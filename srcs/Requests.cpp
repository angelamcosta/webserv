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

void Requests::handleRequest(int sockfd, Server &server) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0);
    if (bytes_received > server.getBodySize()) {
        std::string response = "HTTP/1.1 413 Request Entity Too Large\r\n\r\n";
        sendResponse(sockfd, response);
        return;
    }
    if (bytes_received < 0) {
        close(sockfd);
        return;
    }
    buffer[bytes_received] = '\0';
    std::string request(buffer);
    t_request data = processRequest(request);
    setData(data, server, request);
    printRequest(data);
    Processes::createProcess(sockfd, data);
}

void Requests::handleConn(std::vector<struct pollfd> &fds,
                          std::vector<Server> &servers) {
    while (1) {
        int ret = poll(fds.data(), fds.size(), TIMEOUT);
        if (ret < 0) {
            perror("poll");
            exit(EXIT_FAILURE);
        } else if (ret == 0)
            continue;
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
                handleRequest(client_fd, servers[i]);
                close(client_fd);
                fds[i].revents = 0;
            }
        }
    }
}

void Requests::sendResponse(int sockfd, const std::string &response) {
    if (send(sockfd, response.c_str(), response.size(), 0) < 0) {
        Processes::handleError("Error sending response");
    }
    close(sockfd);
}

t_request Requests::processRequest(const std::string &request) {
    std::istringstream iss(request);
    std::string line;
    std::string method, url;

    while (std::getline(iss, line)) {
        if (line.find("HTTP/") != std::string::npos) {
            std::istringstream line_stream(line);
            line_stream >> method >> url;
        }
    }
    t_request data;
    data.url = url;
    data.method = method;
    return (data);
}

void Requests::setData(t_request &data, Server &server, const std::string &request) {
    data.index = server.getIndex();
    data.request = request;
    data.path_info = server.getRoot();
    data.error_page = server.getErrorPage();
    data.dir_listing = server.getDirListing();
    data.allowed_methods = server.getUrlMethods(data.url);
}

void Requests::printRequest(const t_request& req) {
    std::cout << "\n------\nURL: " << req.url << std::endl;
    std::cout << "Request: " << req.request << std::endl;
    std::cout << "Index: " << req.index << std::endl;
    std::cout << "Method: " << req.method << std::endl;
    std::cout << "Path Info: " << req.path_info << std::endl;
    std::cout << "Error Page: " << req.error_page << std::endl;
    std::cout << "Directory Listing: " << req.dir_listing << std::endl;
    std::cout << "Allowed Methods: " << req.allowed_methods << "\n------\n" << std::endl;
}
