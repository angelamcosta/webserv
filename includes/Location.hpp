/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:10:30 by anlima            #+#    #+#             */
/*   Updated: 2024/05/10 14:42:07 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "Directive.hpp"
#include "macros.hpp"

class Location {
  private:
    std::string _path;
    std::string _index;
    std::vector<Directive> _directives;
    std::vector<Location> _locations;

  public:
    Location();
    ~Location();
    Location(const Location &copy);
    Location &operator=(const Location &copy);
    Location(const std::string path);

    const std::string &getPath(void) const;
    void setPath(std::string path);
    
    const std::vector<Directive> &getDirectives(void) const;
    void addDirective(const Directive &directive);
    
    const std::vector<Location> &getLocations(void) const;
    void addLocation(Location location);

    const std::string &getIndex(void) const;
    void setIndex(std::string index);
};

#endif
