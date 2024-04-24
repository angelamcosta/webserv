/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:57 by anlima            #+#    #+#             */
/*   Updated: 2024/04/24 14:32:21 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "Directive.hpp"
#include "Location.hpp"
#include "Server.hpp"
#include "macros.hpp"

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <poll.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

std::vector<Server> parse_conf(std::string filename);
void process_location(const std::string &line, Server &server);
void process_directive(const std::string &line, Server &server);
void process_directive(const std::string &line, Location &location);
void process_line(const std::string &line, std::vector<Server> &servers);

void welcome_text(void);

void create_process(int server_socket, int client_socket);

void handle_request(int sockfd);
std::map<std::string, std::string> get_params(std::string url);

int bind_socket(int sockfd);
int start_server(int sockfd);
int create_server_socket(void);

std::string mime_type(void);
std::string dynamic_content(std::string content_str,
                            std::map<std::string, std::string> params);
void serve_file(int client_socket, std::string const &file_path,
                std::map<std::string, std::string> params);

#endif
