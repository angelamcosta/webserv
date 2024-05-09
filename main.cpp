/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:03 by anlima            #+#    #+#             */
/*   Updated: 2024/05/09 18:32:57 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Directive.hpp"
#include "includes/Location.hpp"
#include "includes/Methods.hpp"
#include "includes/Parser.hpp"
#include "includes/Processes.hpp"
#include "includes/Requests.hpp"
#include "includes/Server.hpp"
#include "includes/Sockets.hpp"
#include "includes/macros.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        Processes::handle_error("Error! Usage => ./webserv <config filename>");
        return (1);
    }
    try {
        std::vector<struct pollfd> fds;
        std::vector<Server> servers = Parser::parse_conf(argv[1]);

        for (size_t i = 0; i < servers.size(); ++i) {
            servers[i].setSocket(Sockets::create_server_socket());
            Sockets::bind_socket(servers[i].getSocket(), servers[i].getPort());
            Sockets::start_server(servers[i].getSocket());
            servers[i].setPollfd(Sockets::create_pollfd(servers[i].getSocket()));
            fds.push_back(servers[i].getPollfd());
        }
        Requests::handle_conn(fds, servers);
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    return (0);
}
