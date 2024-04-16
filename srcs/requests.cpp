/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requests.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:42:03 by anlima            #+#    #+#             */
/*   Updated: 2024/04/16 19:05:53 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../webserv.hpp"

void    handle_request(int sockfd);

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
    std::cout << "Handling request for client socket: " << sockfd << std::endl;
    serve_file(sockfd, "/home/anlima/webserv/public/index.html");
}
