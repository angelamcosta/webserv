/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requests.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:42:03 by anlima            #+#    #+#             */
/*   Updated: 2024/04/24 14:33:08 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

void handle_request(int sockfd);
std::map<std::string, std::string> get_params(std::string url);

void handle_request(int sockfd) {
    char buffer[BUFFER_SIZE];

    ssize_t bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0);
    if (bytes_received < 0) {
        std::cout << "Error in receiving request" << std::endl;
        close(sockfd);
        return;
    }
    buffer[bytes_received] = '\0';
    std::string request(buffer);
    std::istringstream iss(request);
    std::string method, url, protocol;
    iss >> method >> url >> protocol;
    std::cout << "Received request:\n" << buffer << std::endl;
    std::cout << "Handling request for client socket: " << sockfd << std::endl;
    std::map<std::string, std::string> params = get_params(url);
    serve_file(sockfd, "/home/anlima/webserv/public/index.html", params);
}

std::map<std::string, std::string> get_params(std::string url) {
    std::map<std::string, std::string> params;

    size_t pos = url.find('?');
    if (pos == std::string::npos)
        return (params);

    std::string query = url.substr(pos + 1);

    std::istringstream iss(query);
    std::string pair;
    while (std::getline(iss, pair, '&')) {
        size_t equal_pos = pair.find('=');
        if (equal_pos != std::string::npos) {
            std::string key = pair.substr(0, equal_pos);
            std::string value = pair.substr(equal_pos + 1);
            params[key] = value;
        }
    }
    return params;
}
