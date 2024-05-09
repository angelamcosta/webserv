/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sockets.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:22:09 by anlima            #+#    #+#             */
/*   Updated: 2024/05/09 17:31:58 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETS_HPP
#define SOCKETS_HPP

#include "macros.hpp"

class Sockets {
  private:
    Sockets();

  public:
    static void start_server(int sockfd);
    static int create_server_socket(void);
    static void set_non_blocking(int sockfd);
    static void bind_socket(int sockfd, int port);
    static struct pollfd create_pollfd(int sock_fd);
};

#endif
