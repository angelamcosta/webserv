/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:29:09 by anlima            #+#    #+#             */
/*   Updated: 2024/04/24 14:33:02 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

// just for testing purposes
void create_process(int server_socket, int client_socket);

void create_process(int server_socket, int client_socket) {
    pid_t pid = fork();

    if (pid < 0)
        close(client_socket);
    else if (pid == 0) {
        close(server_socket);
        handle_request(client_socket);
        close(client_socket);
        exit(0);
    } else
        close(client_socket);
}
