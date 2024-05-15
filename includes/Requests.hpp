/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Requests.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:20:33 by anlima            #+#    #+#             */
/*   Updated: 2024/05/15 20:18:57 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTS_HPP
#define REQUESTS_HPP

#include "Processes.hpp"
#include "Server.hpp"
#include "macros.hpp"

class Requests {
  private:
    Requests();

  public:
    static void handleRequest(int sockfd, Server server);
    static void sendResponse(int sockfd, const std::string &response);
    static void handleConn(std::vector<struct pollfd> &fds,
                            std::vector<Server> &servers);
    static std::string generateResponse(const std::string &status,
                                         const std::string &file);
    static std::string readFile(const std::string &filename);
    static t_request processRequest(const std::string &request);
    static std::string extractFilename(const std::string &content_type);
    static std::string extractBody(const std::string &request);
};

#endif