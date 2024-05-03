/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:22:09 by anlima            #+#    #+#             */
/*   Updated: 2024/05/03 16:42:27 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Server.hpp"

Server::Server() {}
Server::~Server() {}

Server::Server(const Server &other)
    : _root(other._root), _index(other._index), _locations(other._locations),
      _directives(other._directives), _socket(other._socket), _fd(other._fd) {}

Server &Server::operator=(const Server &other) {
    if (this != &other) {
        _root = other._root;
        _index = other._index;
        _locations = other._locations;
        _directives = other._directives;
        _socket = other._socket;
        _fd = other._fd;
    }
    return *this;
}

std::vector<Location> &Server::getLocations(void) { return (_locations); }
std::vector<Directive> &Server::getDirectives(void) { return (_directives); }

void Server::addLocation(Location location) { _locations.push_back(location); }

void Server::addDirective(Directive directive) {
    if (directive.getName() == "root")
        setRoot(directive.getValue());
    else if (directive.getName() == "index")
        setIndex(directive.getValue());
    else
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

std::string Server::getRoot(void) { return (_root); }
void Server::setRoot(std::string root) { _root = root; }

std::string Server::getIndex(void) { return (_index); }
void Server::setIndex(std::string index) { _index = index; }
