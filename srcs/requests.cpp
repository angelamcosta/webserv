/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requests.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:42:03 by anlima            #+#    #+#             */
/*   Updated: 2024/04/24 17:26:21 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

void handle_request(int sockfd);

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
    create_process(sockfd);
}
