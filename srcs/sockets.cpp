/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sockets.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:54:32 by anlima            #+#    #+#             */
/*   Updated: 2024/04/24 14:33:13 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

int bind_socket(int sockfd);
int start_server(int sockfd);
int create_server_socket(void);

int bind_socket(int sockfd) {
    struct sockaddr_in socket_addr;
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = INADDR_ANY;
    socket_addr.sin_port = htons(PORT);

    int bind_res =
        bind(sockfd, (struct sockaddr *)&socket_addr, sizeof(socket_addr));
    return (bind_res);
}

int start_server(int sockfd) {
    if (sockfd < 0) {
        std::cout << "Error creating server socket" << std::endl;
        return (0);
    }
    if (bind_socket(sockfd) < 0) {
        std::cout << "Error binding server socket" << std::endl;
        close(sockfd);
        return (0);
    }
    if (listen(sockfd, SOMAXCONN) < 0) {
        std::cout << "Error in listening for connections" << std::endl;
        close(sockfd);
        return (0);
    }
    return (1);
}

int create_server_socket(void) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    return (sockfd);
}
