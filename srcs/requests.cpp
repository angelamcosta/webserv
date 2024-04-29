/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requests.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:42:03 by anlima            #+#    #+#             */
/*   Updated: 2024/04/29 16:44:53 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

void handle_request(int sockfd);
void check_events(std::vector<struct pollfd> &fds, int server_socket);

void handle_request(int sockfd) {
    char buffer[BUFFER_SIZE];

    ssize_t bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0);
    if (bytes_received < 0) {
        handle_error("Error in receiving request");
        close(sockfd);
        return;
    }
    buffer[bytes_received] = '\0';
    std::string request(buffer);
    std::istringstream iss(request);
    std::string method, url, protocol;
    iss >> method >> url >> protocol;
    size_t pos = url.find('?');
    std::string query_string;
    if (pos != std::string::npos)
        query_string = url.substr(pos + 1);
    std::cout << query_string << std::endl;
    create_process(sockfd, query_string);
}

// TODO : - adapt to multiple servers
void check_events(std::vector<struct pollfd> &fds, int server_socket) {
    int nb_events = poll(&fds[0], fds.size(), -1);
    if (nb_events == -1)
        throw std::runtime_error("Error in poll");
    if (fds[0].revents && POLLIN) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(
            server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == -1)
            throw std::runtime_error("Error accepting client connection");
        fds.push_back(create_pollfd(client_socket));
        fds[0].revents = 0;
    }
    for (size_t i = 1; i < fds.size(); ++i) {
        if (fds[i].revents && POLLIN) {
            handle_request(fds[i].fd);
            fds[i].revents = 0;
        }
    }
}
