/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sockets.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:22:09 by anlima            #+#    #+#             */
/*   Updated: 2024/05/15 19:37:07 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETS_HPP
#define SOCKETS_HPP

#include "macros.hpp"

class Sockets {
  private:
    Sockets();

  public:
    static void startServer(int sockfd);
    static int createServerSocket(void);
    static void setNonBlocking(int sockfd);
    static void bindSocket(int sockfd, int port);
    static struct pollfd createPollfd(int sock_fd);
};

#endif
