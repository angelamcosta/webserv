/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sockets.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:22:09 by anlima            #+#    #+#             */
/*   Updated: 2025/03/27 15:30:44 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETS_HPP
#define SOCKETS_HPP

#include "macros.hpp"

class Sockets {
  private:
    Sockets();

  public:
    static void setNonBlocking(int sockfd);
    static int createSocket(struct addrinfo *res);
    static void bindSocket(int sockfd, struct addrinfo *res);
    static void startServer(int sockfd, struct addrinfo *res);
    static int createServer(const std::string &serverName, const std::string &port);
};

#endif
