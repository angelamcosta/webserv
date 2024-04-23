/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:10:30 by anlima            #+#    #+#             */
/*   Updated: 2024/04/23 16:33:09 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <vector>
#include <iostream>
#include "Directive.hpp"

class Location {
    private:
        std::string _path;
        std::vector<Directive> _directives;
        std::vector<Location> _locations;
    public:
        Location();
        ~Location();
        Location(const Location& copy);
        Location &operator=(const Location& copy);
        Location(const std::string path);

        const std::string &getPath(void) const;
        const std::vector<Directive> &getDirectives(void) const;
        void addDirective(const Directive &directive);
        void setPath(std::string path);
        std::vector<Location>& getLocations(void);
        void addLocation(Location location);
};

#endif
