/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:03 by anlima            #+#    #+#             */
/*   Updated: 2024/05/01 18:56:23 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/webserv.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        handle_error("Error! Usage => ./webserv <config filename>");
        return (1);
    }
    try {
        std::vector<struct pollfd> fds;
        std::vector<Server> servers = parse_conf(argv[1]);

        for (size_t i = 0; i < servers.size(); ++i) {
            servers[i].setSocket(create_server_socket());
            bind_socket(servers[i].getSocket(), servers[i].getPort());
            start_server(servers[i].getSocket());
            servers[i].setPollfd(create_pollfd(servers[i].getSocket()));
            fds.push_back(servers[i].getPollfd());
        }
        handle_conn(fds);
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    return (0);
}
