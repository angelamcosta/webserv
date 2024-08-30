/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sockets.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:22:09 by anlima            #+#    #+#             */
/*   Updated: 2024/08/30 15:23:23 by mpedroso         ###   ########.fr       */
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
    static struct pollfd createPollfd(int sock_fd);
    static void bindSocket(int sockfd, struct addrinfo *res);
    static void startServer(int sockfd, struct addrinfo *res);
    static std::vector<int> createServer(const std::string &serverName, const std::string &port);
};

#endif
