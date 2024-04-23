/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:57 by anlima            #+#    #+#             */
/*   Updated: 2024/04/23 17:10:11 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include "macros.hpp"
#include "Server.hpp"
#include "Location.hpp"
#include "Directive.hpp"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <fcntl.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

std::vector<Server> parse_conf(std::string filename);
void process_location(const std::string &line, Server &server);
void process_directive(const std::string &line, Server &server);
void process_directive(const std::string &line, Location &location);
void process_line(const std::string &line, std::vector<Server> &servers);

void    welcome_text(void);

void    create_process(int server_socket, int client_socket);

void    handle_request(int sockfd);
std::map<std::string, std::string>  get_params(std::string url);

int bind_socket(int sockfd);
int start_server(int sockfd);
int create_server_socket(void);

std::string mime_type(void);
std::string dynamic_content(std::string content_str, std::map<std::string, std::string> params);
void    serve_file(int client_socket, std::string const &file_path,std::map<std::string, std::string> params);

#endif
