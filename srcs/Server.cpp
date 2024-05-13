/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:22:09 by anlima            #+#    #+#             */
/*   Updated: 2024/05/13 15:50:53 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

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
    return (*this);
}

const std::vector<Location> &Server::getLocations(void) const { return (_locations); }
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

std::string Server::getFullPath(const std::string &url) {
    if (url.empty() || url == "/")
        return (_root + "/" + _index);
    std::string full_path = findUrl(_locations, "", url);
    if (full_path.empty())
        return (_root + ERROR_PAGE);
    return (full_path);
}

std::string Server::findUrl(const std::vector<Location>& locations, const std::string& curr_path, const std::string& url) {
    for (std::vector<Location>::const_iterator it = locations.begin(); it != locations.end(); ++it) {
        const Location& loc = *it;
        std::string path = curr_path + loc.getPath();
        if (url.find(path) == 0) {
            size_t found = url.find(HTML_EXT);
            if (found == std::string::npos && is_dir(_root + url))
                return (_root + url + "/" + loc.getIndex());
            return (_root + url);
        }
        if (!loc.getLocations().empty()) {
            std::string sub_path = findUrl(loc.getLocations(), path, url);
            if (!sub_path.empty()) {
                return (sub_path);
            }
        }
    }
    return std::string();
}

int Server::is_dir(const std::string &path) {
    DIR* dir = opendir(path.c_str());
    if (dir) {
        closedir(dir);
        return (1);
    }
    return (0);
}
