/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:57 by anlima            #+#    #+#             */
/*   Updated: 2024/05/01 18:16:46 by anlima           ###   ########.fr       */
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
#include <arpa/inet.h>

std::vector<Server> parse_conf(std::string filename);
void process_location(const std::string &line, Server &server);
void process_directive(const std::string &line, Server &server);
void process_directive(const std::string &line, Location &location);
void process_line(const std::string &line, std::vector<Server> &servers);

void welcome_text(void);
struct pollfd create_pollfd(int sock_fd);

int execute_cgi(void);
int redirect_stdout(int pipefd[2]);
void handle_error(std::string message);
void read_output(int sockfd, int pipefd[2]);
void create_process(int sockfd, const std::string &query_string);

void handle_request(int sockfd);
void handle_conn(std::vector<struct pollfd> fds);

void start_server(int sockfd);
int create_server_socket(void);
void bind_socket(int sockfd, int port);

#endif
