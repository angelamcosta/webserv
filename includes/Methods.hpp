/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Methods.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:15:19 by anlima            #+#    #+#             */
/*   Updated: 2024/05/09 17:26:00 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODS_HPP
#define METHODS_HPP

#include "macros.hpp"
#include "Server.hpp"

class Methods {
  private:
    Methods();

  public:
    static void get_request(int sockfd, Server server, const std::string &full_path);
    static void handle_method(int sockfd, Server server, const std::string &full_path,
                       const std::string &method);
};

#endif