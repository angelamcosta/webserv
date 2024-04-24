/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:22:09 by anlima            #+#    #+#             */
/*   Updated: 2024/04/24 14:32:51 by anlima           ###   ########.fr       */
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
