/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:22:09 by anlima            #+#    #+#             */
/*   Updated: 2025/03/21 13:25:38 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Server::Server()
    : _cgi(""), _root(""), _index(""), _error_page(""), _server_name(""), _port(""),
      _socket(0), _body_size(0), _dir_listing("on") {}
Server::~Server() {}

Server::Server(const Server &other)
{
    _cgi = other._cgi;
    _root = other._root;
    _index = other._index;
    _error_page = other._error_page;
    _server_name = other._server_name;
    _locations = other._locations;
    _directives = other._directives;
    _port = other._port;
    _socket = other._socket;
    _body_size = other._body_size;
    _dir_listing = other._dir_listing;
    _fds = other._fds;
    _url_methods = other._url_methods;
}

Server &Server::operator=(const Server &other)
{
    if (this != &other)
    {
        _cgi = other._cgi;
        _root = other._root;
        _index = other._index;
        _error_page = other._error_page;
        _server_name = other._server_name;
        _locations = other._locations;
        _directives = other._directives;
        _port = other._port;
        _socket = other._socket;
        _body_size = other._body_size;
        _dir_listing = other._dir_listing;
        _fds = other._fds;
        _url_methods = other._url_methods;
    }
    return (*this);
}

const std::vector<Location> &Server::getLocations(void) const
{
    return (_locations);
}
std::vector<Directive> &Server::getDirectives(void) { return (_directives); }

void Server::addLocation(Location location) { _locations.push_back(location); }

void Server::addDirective(Directive directive)
{
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
    else if (directive.getName() == "autoindex")
        setDirListing(directive.getValue());
    else if (directive.getName() == "error_page")
        setErrorPage(directive.getValue());
    else if (directive.getName() == "cgi")
        setCgi(directive.getValue());
    else
        throw std::invalid_argument("Error: Invalid directive.");
    _directives.push_back(directive);
}

const std::string &Server::getCgi(void) { return (_cgi); }
void Server::setCgi(const std::string &cgi) { _cgi = cgi; }

const std::string Server::getPort(void) { return (_port != "" ? _port : "8080"); }
void Server::setPort(const std::string &port)
{
    if (_port == "")
        _port = port;
    else
        _port += " " + port;
}

std::vector<int> Server::getSocket(void) { return (_socket); }
void Server::setSocket(const std::vector<int> &socket) { _socket = socket; }

long Server::getBodySize(void) { return (_body_size); }
void Server::setBodySize(const std::string &body_size)
{
    long value = 0;
    std::istringstream iss(body_size);

    checkBodySize(body_size);
    if (!(iss >> value))
        throw std::invalid_argument("Error: Invalid body size: " + body_size);
    if (value < 0)
        throw std::invalid_argument("Error: Invalid body size: " + body_size);
    _body_size = value;
}

const std::string &Server::getDirListing(void) const { return (_dir_listing); }
void Server::setDirListing(const std::string &dir_listing)
{
    if (dir_listing == "on" || dir_listing == "off")
        _dir_listing = dir_listing;
    else
        throw std::invalid_argument("Error: Invalid autoindex option: " +
                                    dir_listing);
}

std::vector<struct pollfd> Server::getPollfd(void) { return (_fds); }
void Server::setPollfd(struct pollfd fd) { _fds.push_back(fd); }

const std::string &Server::getRoot(void) { return (_root); }
void Server::setRoot(const std::string &root) { _root = root; }

const std::string &Server::getIndex(void) { return (_index); }
void Server::setIndex(const std::string &index) { _index = index; }

const std::string &Server::getServerName(void) { return (_server_name); }
void Server::setServerName(const std::string &server_name) { _server_name = server_name; }

const std::string Server::getErrorPage(void) { return (_error_page != "" ? _error_page : "/error.html"); }
void Server::setErrorPage(const std::string &error_page) { _error_page = error_page; }

const std::string Server::getUrlMethods(const std::string &url)
{
    if (url.empty())
        return ("Not Found");
    for (std::map<std::string, std::string>::iterator it = _url_methods.begin(); it != _url_methods.end(); ++it) {
        if (url.find(it->first) != std::string::npos)
            return (it->second);
    }
    return ("GET");
}

void Server::addUrlMethod(std::string line, std::string url)
{
    size_t pos = line.find_first_of("s") + 2;
    std::string methods = line.substr(pos);
    _url_methods[url] = methods;
}

const Location *Server::findLocation(const std::string &path, const std::vector<Location> &locations)
{
    for (std::vector<Location>::const_iterator it = locations.begin(); it != locations.end(); ++it)
    {
        if (it->getPath() == path)
            return &(*it);
        const Location *subLocation = findLocation(path, it->getLocations());
        if (subLocation)
            return (subLocation);
    }
    return (NULL);
}

void Server::checkBodySize(const std::string &body_size)
{
    for (size_t i = 0; i < body_size.length(); ++i)
    {
        if (!isdigit(body_size[i]))
            throw std::invalid_argument("Error: Invalid char in body size: " + body_size);
    }
}

size_t Server::getServerByFd(pollfd fd, std::vector<Server> &servers)
{
    for (size_t i = 0; i < servers.size(); ++i)
    {
        for (size_t j = 0; j < servers[i].getPollfd().size(); ++j)
        {
            if (fd.fd == servers[i].getPollfd()[j].fd)
                return i;
        }
    }
    return -1;
}

size_t Server::checkDirectives(const std::string &name)
{
    for (size_t i = 0; i < _directives.size(); ++i)
    {
        if (name == _directives[i].getName())
            return 1;
    }
    return 0;
}
