/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Requests.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:20:33 by anlima            #+#    #+#             */
/*   Updated: 2024/05/23 20:29:23 by anlima           ###   ########.fr       */
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
    static void handleRequest(int sockfd, Server &server);
    static std::string extractBody(const std::string &request);
    static t_request processRequest(const std::string &request);
    static void sendResponse(int sockfd, const std::string &response);
    static void setData(t_request &data, Server &server, const std::string &request);
    static void executeCGIScript(int sockfd, Server &server, const t_request &request);
    static void handleConn(std::vector<struct pollfd> &fds, std::vector<Server> &servers);
    static void printRequest(const t_request& req);
};

#endif