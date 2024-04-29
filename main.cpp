/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:03 by anlima            #+#    #+#             */
/*   Updated: 2024/04/29 16:45:17 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/webserv.hpp"

int main(int argc, char **argv) {
    if (argc == 2) {
        try {
            std::vector<struct pollfd> fds;
            std::vector<Server> server_list = parse_conf(argv[1]);

            for (size_t i = 0; i < server_list.size(); ++i) {
                int server_socket = create_server_socket();
                int port = server_list[i].getPort();
                if (start_server(server_socket, port)) {
                    struct pollfd server_pollfd = create_pollfd(server_socket);
                    fds.push_back(server_pollfd);
                }
            }
            // TODO : - Add main event loop
            for (size_t i = 0; i < fds.size(); ++i) {
                close(fds[i].fd);
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }
    } else
        handle_error("Error in usage [./webserv <conf file>]");
    return (0);
}
