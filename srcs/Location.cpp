/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:24:24 by anlima            #+#    #+#             */
/*   Updated: 2024/05/10 14:41:52 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Location.hpp"

Location::Location() {}
Location::~Location() {}
Location::Location(const Location &copy) : _path(copy._path), _index(copy._index), _directives(copy._directives), _locations(copy._locations) {}

Location &Location::operator=(const Location &copy) {
    if (this != &copy) {
        _path = copy._path;
        _index = copy._index;
        _directives = copy._directives;
        _locations = copy._locations;
    }
    return (*this);
}

Location::Location(const std::string path) { _path = path; }

const std::string &Location::getPath(void) const { return (_path); }
const std::vector<Directive> &Location::getDirectives(void) const {
    return (_directives);
}

void Location::setPath(std::string path) { _path = path; }
void Location::addDirective(const Directive &directive) {
    if (directive.getName() == "index")
        setIndex(directive.getValue());
    else
        _directives.push_back(directive);
}

const std::vector<Location> &Location::getLocations(void) const { return (_locations); }
void Location::addLocation(Location location) {
    _locations.push_back(location);
}

const std::string &Location::getIndex(void) const { return (_index); }
void Location::setIndex(std::string index) { _index = index; }