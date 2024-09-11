/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva <gsilva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:24:24 by anlima            #+#    #+#             */
/*   Updated: 2024/09/11 15:36:55 by gsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Location.hpp"

Location::Location() : _path(""), _index(""), _allow_methods("") {}
Location::~Location() {}
Location::Location(const Location &copy)
    : _path(copy._path), _index(copy._index), _allow_methods(copy._allow_methods), _directives(copy._directives),
      _locations(copy._locations) {}

Location &Location::operator=(const Location &copy) {
    if (this != &copy) {
        _path = copy._path;
        _index = copy._index;
        _allow_methods = copy._allow_methods;
        _directives = copy._directives;
        _locations = copy._locations;
    }
    return (*this);
}

Location::Location(const std::string &path) { _path = path; }

const std::string &Location::getPath(void) const { return (_path); }
const std::vector<Directive> &Location::getDirectives(void) const {
    return (_directives);
}

void Location::setPath(const std::string &path) { _path = path; }
void Location::addDirective(const Directive &directive) {
    if (directive.getName() == "index")
        setIndex(directive.getValue());
    else if (directive.getName() == "allow_methods")
        setMethods(directive.getValue());
    _directives.push_back(directive);
}

const std::vector<Location> &Location::getLocations(void) const {
    return (_locations);
}
void Location::addLocation(Location location) {
    _locations.push_back(location);
}

const std::string &Location::getMethods(void) const { return (_allow_methods); }
void Location::setMethods(const std::string &methods) {
	std::stringstream iss(methods);
	std::string     method;
	
	if (methods.empty())
		throw std::invalid_argument("Error: Methods not specified.");
	while (iss >> method) {
		if (method != "GET" && method != "POST" && method != "DELETE")
			throw std::invalid_argument("Error: Method not allowed.");
    }
    _allow_methods = methods;
}

const std::string &Location::getIndex(void) const { return (_index); }
void Location::setIndex(const std::string &index) { _index = index; }

size_t  Location::checkDirectives(const std::string &name) {
    for (size_t i = 0; i < _directives.size(); ++i) {
        if (name == _directives[i].getName())
            return 1;
    }
    return 0;
}
