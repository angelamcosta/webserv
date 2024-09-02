/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Requests.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:42:03 by anlima            #+#    #+#             */
/*   Updated: 2024/08/30 15:51:47 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Requests.hpp"

void Requests::handleRequest(int sockfd, Server &server,
                             std::string &response) {
    int read_header = 0;
    std::string request;
    ssize_t bytes_received;
    int content_length = -1;
    char buffer[BUFFER_SIZE];

    while (true) {
        bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            close(sockfd);
            response.clear();
            return;
        }
        if (bytes_received > 0) {
            request.append(buffer, bytes_received);
            if (!read_header)
                findHeaderEnd(request, read_header, content_length);
            if (read_header && readAll(request, content_length))
                break;
        }
    }

    t_request data = processRequest(request, server);
	if (server.getBodySize() < (int)request.length())
		data.method = "invalid_size";
    if (request.find("DELETE") != std::string::npos)
        data.method = "DELETE";
    if (request.find("_filename") != std::string::npos)
        data.filename = getFilename(request);
    response = Processes::createProcess(data);
}

void Requests::findHeaderEnd(const std::string &request, int &read_header,
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

int Requests::readAll(const std::string &request, int content_length) {
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

void Requests::handleConn(std::vector<struct pollfd> fds, std::vector<Server> &servers) {
    std::map<int, std::string> responses;
    while (1) {
        int ret = poll(&fds[0], fds.size(), TIMEOUT);
        if (ret < 0) {
            perror("poll");
            exit(EXIT_FAILURE);
        } else if (ret == 0)
            continue;
        for (size_t i = 0; i < fds.size(); ++i) {
            if (fds[i].revents & (POLLIN | POLLOUT)) {
                if (fds[i].revents & POLLIN) {
                    struct sockaddr_in client_addr;
                    socklen_t client_len = sizeof(client_addr);
                    int client_fd =
                        accept(fds[i].fd, (struct sockaddr *)&client_addr,
                               &client_len);
                    if (client_fd < 0) {
                        perror("accept");
                        continue;
                    }
                    size_t server = Server::getServerByFd(fds[i], servers);
                    std::string response;
                    handleRequest(client_fd, servers[server], response);
                    if (!response.empty()) {
                        struct pollfd new_fd;
                        new_fd.fd = client_fd;
                        new_fd.events = POLLOUT;
                        new_fd.revents = 0;
                        fds.push_back(new_fd);
                        responses[client_fd] = response;
                    } else {
                        close(client_fd);
                    }
                }
                if (fds[i].revents & POLLOUT) {
                    int client_fd = fds[i].fd;
                    if (responses.find(client_fd) != responses.end()) {
                        Requests::sendResponse(client_fd, responses[client_fd]);
                        responses.erase(client_fd);
                        close(client_fd);
                        fds.erase(fds.begin() + i);
                        --i;
                    }
                }
                fds[i].revents = 0;
            }
        }
    }
}

void Requests::sendResponse(int sockfd, const std::string &response) {
    size_t length = response.size();
    const char *data = response.data();

    size_t total_sent = 0;
    while (total_sent < length) {
        ssize_t sent = send(sockfd, data + total_sent, length - total_sent, 0);
        if (sent < 0) {
            perror("send");
            break;
        }
        total_sent += sent;
    }
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
    data.image_data = base64_encode(image_data);
    if (filename_start == std::string::npos)
        return;
    filename_start += 10;
    size_t filename_end = data.request.find("\"", filename_start);
    data.filename =
        data.request.substr(filename_start, filename_end - filename_start);
}

std::string Requests::base64_encode(const std::string &data) {
    std::string set = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                      "abcdefghijklmnopqrstuvwxyz"
                      "0123456789+/";
    const unsigned char *binary =
        reinterpret_cast<const unsigned char *>(data.c_str());
    size_t data_size = data.size();
    std::vector<unsigned char> encoded_data;
    int i = 0;
    unsigned char block[3];
    unsigned char group[4];

    while (data_size--) {
        block[i++] = *(binary++);
        if (i == 3) {
            group[0] = (block[0] & 0xFC) >> 2;
            group[1] = ((block[0] & 0x03) << 4) + ((block[1] & 0xF0) >> 4);
            group[2] = ((block[1] & 0x0F) << 2) + ((block[2] & 0xC0) >> 6);
            group[3] = block[2] & 0x3F;
            for (i = 0; i < 4; ++i)
                encoded_data.push_back(set[group[i]]);
            i = 0;
        }
    }
    if (i) {
        for (int j = i; j < 3; ++j)
            block[j] = '\0';
        group[0] = (block[0] & 0xFC) >> 2;
        group[1] = ((block[0] & 0x03) << 4) + ((block[1] & 0xF0) >> 4);
        group[2] = ((block[1] & 0x0F) << 2) + ((block[2] & 0xC0) >> 6);
        for (int j = 0; j < i + 1; ++j)
            encoded_data.push_back(set[group[j]]);
        while ((i++ < 3))
            encoded_data.push_back('=');
    }
    return std::string(encoded_data.begin(), encoded_data.end());
}

std::string Requests::getFilename(const std::string &request) {
    std::istringstream iss(request);
    std::string token;
    std::string filename;

    while (std::getline(iss, token, '&')) {
        if (token.find("_filename=") != std::string::npos) {
            filename = token.substr(token.find('=') + 1);
            break;
        }
    }
    return (filename);
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
    std::cout << "Image data: " << data.image_data.substr(0, 100) << std::endl;
}
