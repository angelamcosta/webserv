/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sockets.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:54:32 by anlima            #+#    #+#             */
/*   Updated: 2024/05/17 13:22:09 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Sockets.hpp"

void Sockets::startServer(int sockfd) {
    if (listen(sockfd, SOMAXCONN) < 0) {
        close(sockfd);
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

int Sockets::createServerSocket(void) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    if (sockfd < 0) {
        perror("socket failed");
        return (sockfd);
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    setNonBlocking(sockfd);
    return (sockfd);
}

void Sockets::setNonBlocking(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
    if (fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
}

void Sockets::bindSocket(int sockfd, int port) {
    struct sockaddr_in socket_addr;
    socklen_t addr_len = sizeof(socket_addr);

    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = INADDR_ANY;
    socket_addr.sin_port = htons(port);
    int bind_res = bind(sockfd, (struct sockaddr *)&socket_addr, addr_len);
    if (bind_res < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

struct pollfd Sockets::createPollfd(int sock_fd) {
    struct pollfd sock_pollfd;
    sock_pollfd.fd = sock_fd;
    sock_pollfd.events = POLLIN;
    sock_pollfd.revents = 0;
    return (sock_pollfd);
}
