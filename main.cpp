/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:03 by anlima            #+#    #+#             */
/*   Updated: 2024/03/27 15:32:04 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int main(void)
{
    int server_sockfd;
    int client_sockfd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_sockfd = create_server_socket();
    if (!start_server(server_sockfd))
        return (0);
    std::cout << "Server listening on port " << PORT << std::endl;
    while (true) {
        client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_addr, &client_len);
        if (client_sockfd < 0) {
            std::cout << "Error in accepting connection: " << strerror(errno) << std::endl;
            continue;
        }
        handle_request(client_sockfd);
    }
    close(server_sockfd);
    return (0);
}
