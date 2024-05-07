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
void send_response(int sockfd, const std::string &response);
std::string parse_url(const std::string &url, const std::string &index);
void handle_conn(std::vector<struct pollfd> &fds, std::vector<Server> &servers);
std::string generate_response(const std::string &status, const std::string &file);

void handle_request(int sockfd, Server server) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0);
    if (bytes_received > MAX_BODY_SIZE) {
        std::string response = "HTTP/1.1 413 Request Entity Too Large\r\n\r\n";
        send_response(sockfd, response);
        return ;
    }
    if (bytes_received < 0) {
        close(sockfd);
        return ;
    }
    buffer[bytes_received] = '\0';
    std::string request(buffer);
    std::istringstream iss(request);
    std::string method, url, protocol;
    iss >> method >> url >> protocol;
    url = parse_url(url, server.getIndex());
    std::string full_path = server.getRoot() + url;
    handle_method(sockfd, server, full_path, method);
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

std::string parse_url(const std::string &url, const std::string &index) {
    return (url.empty() || url == "/") ? ("/" + index) : url;
}

std::string generate_response(const std::string &status,
                              const std::string &file) {
    std::string response = "HTTP/1.1 " + status + "\r\nContent-Length: ";
    response += file.size();
    response += "\r\n\r\n";
    response += file;
    return (response);
}
