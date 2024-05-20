/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:06:05 by anlima            #+#    #+#             */
/*   Updated: 2024/05/20 17:45:28 by anlima           ###   ########.fr       */
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
    std::string _server_name;
    std::vector<Location> _locations;
    std::vector<Directive> _directives;
    std::string _port;
    int _socket;
    int _body_size;
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

    std::string getPort(void);
    void setPort(std::string port);

    int getSocket(void);
    void setSocket(int socket);

    struct pollfd getPollfd(void);
    void setPollfd(struct pollfd fd);

    int getBodySize(void);
    void setBodySize(std::string body_size);

    std::string getRoot(void);
    void setRoot(std::string root);

    std::string getIndex(void);
    void setIndex(std::string index);

    std::string getServerName(void);
    void setServerName(std::string server_name);

    std::string getFullPath(const std::string &url);
    std::string findUrl(const std::vector<Location> &locations,
                        const std::string &curr_path, const std::string &url);
    int is_dir(const std::string &path);
};

#endif
