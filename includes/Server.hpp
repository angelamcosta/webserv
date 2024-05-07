/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:06:05 by anlima            #+#    #+#             */
/*   Updated: 2024/05/07 16:38:58 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Directive.hpp"
#include "Location.hpp"
#include <iostream>
#include <poll.h>
#include <sstream>
#include <vector>

class Server {
  private:
    std::string _root;
    std::string _index;
    std::vector<Location> _locations;
    std::vector<Directive> _directives;
    int _socket;
    struct pollfd _fd;

  public:
    Server();
    ~Server();
    Server(const Server &other);
    Server &operator=(const Server &other);

    std::vector<Location> &getLocations(void);
    std::vector<Directive> &getDirectives(void);

    void addLocation(Location location);
    void addDirective(Directive directive);

    int getPort(void);

    int getSocket(void);
    void setSocket(int socket);

    struct pollfd getPollfd(void);
    void setPollfd(struct pollfd fd);

    std::string getRoot(void);
    void setRoot(std::string root);

    std::string getIndex(void);
    void setIndex(std::string index);

    std::string getFullPath(const std::string &url);
};

#endif
