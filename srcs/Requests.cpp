/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Requests.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:42:03 by anlima            #+#    #+#             */
/*   Updated: 2024/05/27 21:25:54 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Requests.hpp"

void Requests::handleRequest(int sockfd, Server &server) {
    int read_header = 0;
    std::string request;
    ssize_t bytes_received;
    int content_length = -1;
    char buffer[BUFFER_SIZE];

    while (true) {
        bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            close(sockfd);
            return;
        }
        if (bytes_received > 0) {
            request.append(buffer, bytes_received);
            if (!read_header)
                find_header_end(request, read_header, content_length);
            if (read_header && read_all(request, content_length))
                break;
        }
    }
    t_request data = processRequest(request, server);
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

t_request Requests::processRequest(const std::string &request, Server &server) {
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
    setData(data, server, request);
    return (data);
}

void Requests::setData(t_request &data, Server &server,
                       const std::string &request) {
    data.index = server.getIndex();
    data.request = request;
    data.path_info = server.getRoot();
    data.error_page = server.getErrorPage();
    data.dir_listing = server.getDirListing();
    data.allowed_methods = server.getUrlMethods(data.url);
    handleImagePost(data);
}

void Requests::printRequest(const t_request &data) {
    std::cout << "\n------\nURL: " << data.url << std::endl;
    std::cout << "Request: " << data.request << std::endl;
    std::cout << "Index: " << data.index << std::endl;
    std::cout << "Method: " << data.method << std::endl;
    std::cout << "Path Info: " << data.path_info << std::endl;
    std::cout << "Error Page: " << data.error_page << std::endl;
    std::cout << "Directory Listing: " << data.dir_listing << std::endl;
    std::cout << "Allowed Methods: " << data.allowed_methods << std::endl;
    std::cout << "Encoded image: " << data.image_data << std::endl;
    std::cout << "Filename: " << data.filename << "\n------\n" << std::endl;
    std::cout << "Data type of image_data: " << typeid(data.image_data).name()
              << std::endl;
    std::cout << "Image data: " << data.image_data.substr(0, 100)
              << std::endl;
}

void Requests::handleImagePost(t_request &data) {
    size_t boundary_start = data.request.find("boundary=");
    if (boundary_start == std::string::npos)
        return;
    size_t boundary_end = data.request.find("\r\n", boundary_start);
    if (boundary_end == std::string::npos)
        return;
    std::string boundary = data.request.substr(
        boundary_start + 9, boundary_end - boundary_start - 9);
    size_t filename_start = data.request.find("filename=\"", boundary_end);
    size_t data_start = data.request.find("\r\n\r\n", filename_start);
    if (data_start == std::string::npos)
        return;
    data_start += 4;
    std::string image_data = data.request.substr(data_start);
    if (filename_start == std::string::npos)
        return;
    filename_start += 10;
    size_t filename_end = data.request.find("\"", filename_start);
    std::string filename =
        data.request.substr(filename_start, filename_end - filename_start);
    data.filename = filename;
    data.image_data = base64_encode(image_data);
}

void Requests::find_header_end(const std::string &request, int &read_header,
                               int &content_length) {
    size_t pos = request.find("\r\n\r\n");

    if (pos != std::string::npos) {
        read_header = 1;
        size_t start = request.find("Content-Length: ", 0);
        if (start != std::string::npos) {
            size_t end = request.find("\r\n", start);
            std::string len_str = request.substr(start + 16, end - start + 16);
            std::stringstream(len_str) >> content_length;
        }
    }
}

int Requests::read_all(const std::string &request, int content_length) {
    size_t pos = request.find("\r\n\r\n");
    if (pos != std::string::npos) {
        if (content_length == -1)
            return (1);
        std::string subs = request.substr(pos + 4);
        if (static_cast<int>(subs.size()) >= content_length)
            return (1);
    }
    return (0);
}

// TODO : - base64_encode implementation