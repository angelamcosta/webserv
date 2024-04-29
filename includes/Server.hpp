/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:06:05 by anlima            #+#    #+#             */
ad/*   Updated: 2024/04/29 16:29:59 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Directive.hpp"
#include "Location.hpp"
#include <iostream>
#include <vector>
#include <sstream>

class Server {
  private:
    std::vector<Location> _locations;
    std::vector<Directive> _directives;
    Server &operator=(const Server &copy);

  public:
    Server();
    ~Server();
    Server(const Server &copy);

    std::vector<Location> &getLocations(void);
    std::vector<Directive> &getDirectives(void);

    void addLocation(Location location);
    void addDirective(Directive directive);

    int getPort(void);
};

#endif
