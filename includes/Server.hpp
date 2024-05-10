/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:06:05 by anlima            #+#    #+#             */
/*   Updated: 2024/05/10 14:54:37 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Directive.hpp"
#include "Location.hpp"
#include "macros.hpp"

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

    const std::vector<Location> &getLocations(void) const;
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
    std::string findUrl(const std::vector<Location>& locations, const std::string &curr_path, const std::string &url);
    int is_dir(const std::string &path);
};

#endif
