/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Requests.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:20:33 by anlima            #+#    #+#             */
/*   Updated: 2024/05/09 17:49:32 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTS_HPP
#define REQUESTS_HPP

#include "macros.hpp"
#include "Server.hpp"
#include "Methods.hpp"
#include "Processes.hpp"

class Requests {
  private:
    Requests();

  public:
    static void handle_request(int sockfd, Server server);
    static void send_response(int sockfd, const std::string &response);
    static void handle_conn(std::vector<struct pollfd> &fds,
                            std::vector<Server> &servers);
    static std::string generate_response(const std::string &status,
                                         const std::string &file);
    static std::string read_file(const std::string &filename);
};

#endif