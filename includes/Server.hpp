/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:06:05 by anlima            #+#    #+#             */
/*   Updated: 2024/04/23 16:25:59 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>
#include <iostream>
#include "Location.hpp"
#include "Directive.hpp"

class Server {
    private:
        std::vector<Location> _locations;
        std::vector<Directive> _directives;
        Server &operator=(const Server& copy);
    public:
        Server();
        ~Server();
        Server(const Server& copy);

        std::vector<Location>& getLocations(void);
        std::vector<Directive> &getDirectives(void);

        void addLocation(Location location);
        void addDirective(Directive directive);
};

#endif
