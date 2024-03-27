/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requests.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:42:03 by anlima            #+#    #+#             */
/*   Updated: 2024/03/27 15:02:28 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int     start_server(int sockfd);
void    handle_request(int sockfd);

int start_server(int sockfd)
{
    if (sockfd < 0)
    {
        std::cout << "Error creating server socket" << std::endl;
        return (0);
    }
    if (bind_socket(sockfd) < 0)
    {
        std::cout << "Error binding server socket" << std::endl;
        close(sockfd);
        return (0);
    }
    if (listen(sockfd, 5) < 0) {
        std::cout << "Error in listening for connections" << std::endl;
        close(sockfd);
        return (0);
    }
    return (1);
}

void handle_request(int sockfd)
{
    char buffer[BUFFER_SIZE];

    ssize_t bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0);
    if (bytes_received < 0) {
        std::cout << "Error in receiving request" << std::endl;
        close(sockfd);
        return;
    }
    buffer[bytes_received] = '\0';
    std::cout << "Received request:\n" << buffer << std::endl;
    ssize_t bytes_sent = send(sockfd, RES, strlen(RES), 0);
    if (bytes_sent < 0) {
        std::cout << "Error in sending response" << std::endl;
    }
    close(sockfd);
}
