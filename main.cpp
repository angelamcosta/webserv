/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:03 by anlima            #+#    #+#             */
/*   Updated: 2024/04/24 15:33:52 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/webserv.hpp"

int main(void) {
    int server_socket;

    server_socket = create_server_socket();
    if (!start_server(server_socket))
        return (0);
    welcome_text();
    while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        handle_request(client_socket);
    }
    close(server_socket);

    return (0);
}
