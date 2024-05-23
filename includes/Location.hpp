/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:10:30 by anlima            #+#    #+#             */
/*   Updated: 2024/05/21 14:52:53 by anlima           ###   ########.fr       */
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
    std::string _allow_methods;
    std::vector<Directive> _directives;
    std::vector<Location> _locations;

  public:
    Location();
    ~Location();
    Location(const Location &copy);
    Location &operator=(const Location &copy);
    Location(const std::string &path);

    const std::string &getPath(void) const;
    void setPath(const std::string &path);
    
    const std::vector<Directive> &getDirectives(void) const;
    void addDirective(const Directive &directive);
    
    const std::vector<Location> &getLocations(void) const;
    void addLocation(Location location);

    const std::string &getIndex(void) const;
    void setIndex(const std::string &index);
    
    const std::string &getMethods(void) const;
    void setMethods(const std::string &methods);
};

#endif
