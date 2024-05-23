/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:06:05 by anlima            #+#    #+#             */
/*   Updated: 2024/05/21 16:46:15 by anlima           ###   ########.fr       */
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
    std::string _error_page;
    std::string _server_name;
    std::vector<Location> _locations;
    std::vector<Directive> _directives;
    std::string _port;
    int _socket;
    int _body_size;
    std::string _dir_listing;
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

    struct pollfd getPollfd(void);
    void setPollfd(struct pollfd fd);

    int getSocket(void);
    void setSocket(int socket);

    int getBodySize(void);
    void setBodySize(const std::string &body_size);

    const std::string &getDirListing(void) const;
    void setDirListing(const std::string &dir_listing);

    const std::string &getPort(void);
    void setPort(const std::string &port);

    const std::string &getRoot(void);
    void setRoot(const std::string &root);

    const std::string &getIndex(void);
    void setIndex(const std::string &index);

    const std::string getErrorPage(void);
    void setErrorPage(const std::string &error_page);

    const std::string &getServerName(void);
    void setServerName(const std::string &server_name);

    const std::string getUrlMethods(const std::string &url);
    const Location *findLocation(const std::string &path, const std::vector<Location> &locations);
};

#endif
