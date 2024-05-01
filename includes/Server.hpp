/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:06:05 by anlima            #+#    #+#             */
/*   Updated: 2024/05/01 17:51:58 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Directive.hpp"
#include "Location.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <poll.h>

class Server {
  private:
    int _socket;
    struct pollfd _fd;
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

    int getSocket(void);
    void setSocket(int socket);

    struct pollfd getPollfd(void);
    void setPollfd(struct pollfd fd);
};

#endif
