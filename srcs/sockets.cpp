/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sockets.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:54:32 by anlima            #+#    #+#             */
/*   Updated: 2024/04/29 16:30:59 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

int create_server_socket(void);
int bind_socket(int sockfd, int port);
int start_server(int sockfd, int port);

int create_server_socket(void) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    return (sockfd);
}

int bind_socket(int sockfd, int port) {
    struct sockaddr_in socket_addr;
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = INADDR_ANY;
    socket_addr.sin_port = htons(port);

    int bind_res =
        bind(sockfd, (struct sockaddr *)&socket_addr, sizeof(socket_addr));
    return (bind_res);
}

int start_server(int sockfd, int port) {
    if (sockfd < 0) {
        throw std::runtime_error("Error creating server socket");
        return (0);
    }
    if (bind_socket(sockfd, port) < 0) {
        close(sockfd);
        throw std::runtime_error("Error binding server socket");
    }
    if (listen(sockfd, SOMAXCONN) < 0) {
        close(sockfd);
        throw std::runtime_error("Error in listening for connections");
    }
    return (1);
}
