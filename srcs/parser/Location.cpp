/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:24:24 by anlima            #+#    #+#             */
/*   Updated: 2024/04/23 16:33:29 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Location.hpp"

Location::Location() {}
Location::~Location() {}
Location::Location(const Location& copy)
{
    _path = copy.getPath();
    for (size_t i = 0; i < copy._directives.size(); ++i)
        _directives.push_back(copy._directives[i]);
}

Location &Location::operator=(const Location& copy)
{
    if (this != &copy)
    {
        _path = copy.getPath();
        for (size_t i = 0; i < copy._directives.size(); ++i)
            _directives.push_back(copy._directives[i]);
    }
    return (*this);
}

Location::Location(const std::string path) { _path = path; }

const std::string &Location::getPath(void) const { return (_path); }
const std::vector<Directive> &Location::getDirectives(void) const { return (_directives); }

void Location::setPath(std::string path) { _path = path; }
void Location::addDirective(const Directive &directive) { _directives.push_back(directive); }

std::vector<Location> &Location::getLocations(void) { return (_locations); }
void Location::addLocation(Location location) { _locations.push_back(location); }
