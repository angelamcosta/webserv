/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Requests.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:20:33 by anlima            #+#    #+#             */
/*   Updated: 2024/08/30 15:44:18 by mpedroso         ###   ########.fr       */
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
    static std::string base64_encode(const std::string &data);
    static std::string getFilename(const std::string &request);
    static void sendResponse(int sockfd, const std::string &response);
    static int readAll(const std::string &request, int content_length);
    static t_request processRequest(const std::string &request, Server &server);
    static void handleRequest(int sockfd, Server &server, std::string &response);
    static void setData(t_request &data, Server &server, const std::string &request);
    static void handleConn(std::vector<struct pollfd> fds, Server &server);
    static void findHeaderEnd(const std::string &request, int &read_header, int &content_length);
};

#endif