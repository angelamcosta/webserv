/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:22:09 by anlima            #+#    #+#             */
/*   Updated: 2024/05/01 17:52:06 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

Server::Server() {}
Server::~Server() {}
Server::Server(const Server &copy) {
    for (size_t i = 0; i < copy._locations.size(); ++i)
        _locations.push_back(copy._locations[i]);
    for (size_t i = 0; i < copy._directives.size(); ++i)
        _directives.push_back(copy._directives[i]);
}

std::vector<Location> &Server::getLocations(void) { return (_locations); }
std::vector<Directive> &Server::getDirectives(void) { return (_directives); }

void Server::addLocation(Location location) { _locations.push_back(location); }

void Server::addDirective(Directive directive) {
    _directives.push_back(directive);
}

int Server::getPort(void) {
    for (size_t i = 0; i < _directives.size(); ++i) {
        if (_directives[i].getName() == "listen") {
            int port;
            std::istringstream(_directives[i].getValue()) >> port;
            return port;
        }
    }
    throw std::invalid_argument("Error: Unable find valid port value.");
}

int Server::getSocket(void) { return (_socket); }
void Server::setSocket(int socket) { _socket = socket; }

struct pollfd Server::getPollfd(void) { return (_fd); }
void Server::setPollfd(struct pollfd fd) { _fd = fd; }
