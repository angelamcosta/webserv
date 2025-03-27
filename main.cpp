/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:03 by anlima            #+#    #+#             */
/*   Updated: 2025/03/27 15:53:27 by anlima           ###   ########.fr       */
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
        std::vector<Server> servers = Parser::parseConf(argv[1]);

        signal(SIGINT, signal_handler);
        for (size_t i = 0; i < servers.size(); ++i) {
            servers[i].setSocket(Sockets::createServer(servers[i].getServerName(), servers[i].getPort()));
        }
        Requests::handleConn(servers);
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
    }
    return (0);
}

// curl -v http://localhost:8080
// curl -X GET http://localhost:8080
// curl -X POST -F "file=@/path/to/file" http://localhost:8080
// curl -X DELETE "localhost:8080/crud/read.html?_method=DELETE&_filename=<filename>"