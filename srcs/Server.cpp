/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:22:09 by anlima            #+#    #+#             */
/*   Updated: 2024/05/17 16:23:26 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Server::Server() {}
Server::~Server() {}

Server::Server(const Server &other) {
    _root = other._root;
    _index = other._index;
    _server_name = other._server_name;
    _locations = other._locations;
    _directives = other._directives;
    _port = other._port;
    _socket = other._socket;
    _body_size = other._body_size;
    _fd = other._fd;
}

Server &Server::operator=(const Server &other) {
    if (this != &other) {
        _root = other._root;
        _index = other._index;
        _server_name = other._server_name;
        _locations = other._locations;
        _directives = other._directives;
        _port = other._port;
        _socket = other._socket;
        _body_size = other._body_size;
        _fd = other._fd;
    }
    return (*this);
}

const std::vector<Location> &Server::getLocations(void) const {
    return (_locations);
}
std::vector<Directive> &Server::getDirectives(void) { return (_directives); }

void Server::addLocation(Location location) { _locations.push_back(location); }

void Server::addDirective(Directive directive) {
    if (directive.getName() == "root")
        setRoot(directive.getValue());
    else if (directive.getName() == "index")
        setIndex(directive.getValue());
    else if (directive.getName() == "listen")
        setPort(directive.getValue());
    else if (directive.getName() == "server_name")
        setServerName(directive.getValue());
    else if (directive.getName() == "client_max_body_size")
        setBodySize(directive.getValue());
    else
        _directives.push_back(directive);
}

int Server::getPort(void) { return (_port); }
void Server::setPort(std::string port) {
    int value = 0;
    std::istringstream iss(port);

    if (!(iss >> value))
        throw std::invalid_argument("Error: Invalid port number: " + port);
    if (value < 0 || value > 65535)
        throw std::invalid_argument("Error: Invalid port number: " + port);
    _port = value;
}

int Server::getSocket(void) { return (_socket); }
void Server::setSocket(int socket) { _socket = socket; }

int Server::getBodySize(void) { return (_body_size); }
void Server::setBodySize(std::string body_size) {
    int value = 0;
    std::istringstream iss(body_size);

    if (!(iss >> value))
        throw std::invalid_argument("Error: Invalid body size: " + body_size);
    if (value < 0)
        throw std::invalid_argument("Error: Invalid body size: " + body_size);
    _body_size = value;
}

struct pollfd Server::getPollfd(void) { return (_fd); }
void Server::setPollfd(struct pollfd fd) { _fd = fd; }

std::string Server::getRoot(void) { return (_root); }
void Server::setRoot(std::string root) { _root = root; }

std::string Server::getIndex(void) { return (_index); }
void Server::setIndex(std::string index) { _index = index; }

std::string Server::getServerName(void) { return (_server_name); }
void Server::setServerName(std::string server_name) {
    _server_name = server_name;
}

std::string Server::getFullPath(const std::string &url) {
    if (url.empty() || url == "/")
        return (_root + "/" + _index);
    std::string full_path = findUrl(_locations, "", url);
    if (full_path.empty())
        return (_root + ERROR_PAGE);
    return (full_path);
}

std::string Server::findUrl(const std::vector<Location> &locations,
                            const std::string &curr_path,
                            const std::string &url) {
    for (std::vector<Location>::const_iterator it = locations.begin();
         it != locations.end(); ++it) {
        const Location &loc = *it;
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
    DIR *dir = opendir(path.c_str());
    if (dir) {
        closedir(dir);
        return (1);
    }
    return (0);
}
