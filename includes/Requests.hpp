/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Requests.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:20:33 by anlima            #+#    #+#             */
/*   Updated: 2024/06/04 18:50:01 by anlima           ###   ########.fr       */
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
    static void handleImagePost(t_request &data);
    static void printRequest(const t_request &data);
    static void handleRequest(int sockfd, Server &server);
    static std::string extractBody(const std::string &request);
    static void sendResponse(int sockfd, const std::string &response);
    static t_request processRequest(const std::string &request, Server &server);
    static void setData(t_request &data, Server &server,
                        const std::string &request);
    static void executeCGIScript(int sockfd, Server &server,
                                 const t_request &request);
    static void handleConn(std::vector<struct pollfd> &fds,
                           std::vector<Server> &servers);
    static void find_header_end(const std::string &request, int &read_header,
                                int &content_length);
    static int read_all(const std::string &request, int content_length);
    static std::string base64_encode(const std::string &data);
    static std::string getFilename(const std::string &request);
};

#endif