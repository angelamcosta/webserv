/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sockets.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:54:32 by anlima            #+#    #+#             */
/*   Updated: 2024/05/01 17:19:36 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

void start_server(int sockfd);
int create_server_socket(void);
void bind_socket(int sockfd, int port);

void start_server(int sockfd) {
    if (listen(sockfd, SOMAXCONN) < 0) {
        close(sockfd);
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

int create_server_socket(void) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    if (sockfd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    return (sockfd);
}

void bind_socket(int sockfd, int port) {
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
