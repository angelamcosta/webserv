/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:03 by anlima            #+#    #+#             */
/*   Updated: 2024/10/24 18:09:16 by mpedroso         ###   ########.fr       */
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

int main(int argc, char **argv) {
    if (argc != 2) {
        Processes::handleError("Error! Usage => ./webserv <config filename>");
        return (1);
    }
    try {
        std::vector<struct pollfd> fds;
        std::vector<Server> servers = Parser::parseConf(argv[1]);

        for (size_t i = 0; i < servers.size(); ++i) {
            servers[i].setSocket(Sockets::createServer(servers[i].getServerName(), servers[i].getPort()));
            for (size_t j = 0; j < servers[i].getSocket().size(); ++j) {
                servers[i].setPollfd(Sockets::createPollfd(servers[i].getSocket()[j]));
                Sockets::setNonBlocking(servers[i].getPollfd()[j].fd);
                fds.push_back(servers[i].getPollfd()[j]);
            }
			servers[i].checkCgi(servers[i].getLocations());
        }
        Requests::handleConn(fds, servers);
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }
    return (0);
}
