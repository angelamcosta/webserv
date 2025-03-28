/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:06:05 by anlima            #+#    #+#             */
/*   Updated: 2025/03/21 13:04:15 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Directive.hpp"
#include "Location.hpp"
#include "macros.hpp"

class Server {
  private:
    std::string _cgi;
    std::string _root;
    std::string _index;
    std::string _error_page;
    std::string _server_name;
    std::vector<Location> _locations;
    std::vector<Directive> _directives;
    std::string _port;
    std::vector<int> _socket;
    long _body_size;
    std::string _dir_listing;
    std::vector<struct pollfd> _fds;
    std::map<std::string, std::string> _url_methods;

  public:
    Server();
    ~Server();
    Server(const Server &other);
    Server &operator=(const Server &other);

    const std::vector<Location> &getLocations(void) const;
    std::vector<Directive> &getDirectives(void);

    void addLocation(Location location);
    void addDirective(Directive directive);

    std::vector<struct pollfd> getPollfd(void);
    void setPollfd(struct pollfd fd);

    std::vector<int> getSocket(void);
    void setSocket(const std::vector<int> &socket);

    long getBodySize(void);
    void setBodySize(const std::string &body_size);

    const std::string &getDirListing(void) const;
    void setDirListing(const std::string &dir_listing);

    const std::string &getCgi(void);
    void setCgi(const std::string &cgi);

    const std::string getPort(void);
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
    void addUrlMethod(std::string line, std::string url);

    void checkBodySize(const std::string &body_size);
    size_t  checkDirectives(const std::string &name);
    static size_t getServerByFd(pollfd fd, std::vector<Server> &servers);
};

#endif
