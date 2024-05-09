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

#include "../includes/Requests.hpp"

void Requests::handle_request(int sockfd, Server server) {
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
    std::string full_path = server.getFullPath(url);
    Methods::handle_method(sockfd, server, full_path, method);
}

void Requests::handle_conn(std::vector<struct pollfd> &fds,
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

void Requests::send_response(int sockfd, const std::string &response) {
    if (send(sockfd, response.c_str(), response.size(), 0) < 0) {
        Processes::handle_error("Error sending response");
    }
    close(sockfd);
}

std::string Requests::generate_response(const std::string &status,
                              const std::string &file) {
    std::string response = "HTTP/1.1 " + status + "\r\nContent-Length: ";
    response += file.size();
    response += "\r\n\r\n";
    response += file;
    return (response);
}

std::string Requests::read_file(const std::string &filename) {
    std::ifstream file(filename.c_str(), std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    std::ostringstream file_content;
    file_content << file.rdbuf();
    file.close();
    return (file_content.str());
}
