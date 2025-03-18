/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva <gsilva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:03 by anlima            #+#    #+#             */
/*   Updated: 2025/03/18 16:54:39 by gsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Directive.hpp"
#include "includes/Location.hpp"
#include "includes/Parser.hpp"
#include "includes/Processes.hpp"
#include "includes/Requests.hpp"
#include "includes/Server.hpp"
#include "includes/Sockets.hpp"
#include "includes/macros.hpp"

void    signal_handler(int sig) {
    if (sig == SIGINT) {
        throw std::runtime_error("\nProcess terminated by signal SIGINT");
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        Processes::handleError("Error! Usage => ./webserv <config filename>");
        return (1);
    }
    try {
        std::vector<struct pollfd> fds;
        std::vector<Server> servers = Parser::parseConf(argv[1]);

        signal(SIGINT, signal_handler);
        for (size_t i = 0; i < servers.size(); ++i) {
            servers[i].setSocket(Sockets::createServer(servers[i].getServerName(), servers[i].getPort()));
            for (size_t j = 0; j < servers[i].getSocket().size(); ++j) {
                servers[i].setPollfd(Sockets::createPollfd(servers[i].getSocket()[j]));
                Sockets::setNonBlocking(servers[i].getPollfd()[j].fd);
                fds.push_back(servers[i].getPollfd()[j]);
            }
        }
        Requests::handleConn(fds, servers);
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }
    return (0);
}
