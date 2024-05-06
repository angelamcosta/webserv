/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requests.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:42:03 by anlima            #+#    #+#             */
/*   Updated: 2024/05/01 18:22:43 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

void handle_request(int sockfd, Server server);
std::string parse_url(const std::string &request);
void send_response(int sockfd, const std::string &response);
void handle_conn(std::vector<struct pollfd> &fds, std::vector<Server> &servers);

void handle_request(int sockfd, Server server) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0);
    if (bytes_received < 0) {
        // TODO : - handle EAGAIN and EWOULDBLOCK errors without closing the socket prematurely
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return;
        handle_error("Error in receiving request");
        close(sockfd);
        return;
    } else if (bytes_received == 0) {
        close(sockfd);
        return;
    }
    buffer[bytes_received] = '\0';
    std::string request(buffer);
    std::string full_path = server.getRoot() + parse_url(request);
    std::ifstream file(full_path.c_str(), std::ios::binary);
    if (!file.is_open()) {
        std::string response = "HTTP/1.1 404 Not Found\r\n\r\n";
        send_response(sockfd, response);
        return;
    }
    std::ostringstream file_content;
    file_content << file.rdbuf();
    file.close();
    std::ostringstream content_size;
    content_size << file_content.str().size();
    std::string response = "HTTP/1.1 200 OK\r\nContent-Length: ";
    response += content_size.str();
    response += "\r\n\r\n";
    response += file_content.str();
    send_response(sockfd, response);
}

void handle_conn(std::vector<struct pollfd> &fds,
                 std::vector<Server> &servers) {
    while (1) {
        int ret = poll(fds.data(), fds.size(), -1);
        if (ret < 0) {
            perror("poll");
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < fds.size(); ++i) {
            if (fds[i].revents & POLLIN) {
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_fd = accept(
                    fds[i].fd, (struct sockaddr *)&client_addr, &client_len);
                if (client_fd < 0) {
                    perror("accept");
                    continue;
                }
                set_non_blocking(client_fd);
                handle_request(client_fd, servers[i]);
                close(client_fd);
                fds[i].revents = 0;
            }
        }
    }
}

void send_response(int sockfd, const std::string &response) {
    if (send(sockfd, response.c_str(), response.size(), 0) < 0) {
        handle_error("Error sending response");
    }
    close(sockfd);
}

std::string parse_url(const std::string &request) {
    std::istringstream iss(request);
    std::string method, url, protocol;
    iss >> method >> url >> protocol;
    return (url.empty() || url == "/") ? "/index.html" : url;
}
