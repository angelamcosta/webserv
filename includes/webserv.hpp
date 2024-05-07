/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:57 by anlima            #+#    #+#             */
/*   Updated: 2024/05/07 16:10:02 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "Directive.hpp"
#include "Location.hpp"
#include "Server.hpp"
#include "macros.hpp"

#include <arpa/inet.h>
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

std::vector<Server> parse_conf(const std::string &filename);
void process_location(const std::string &line, Server &server);
void process_directive(const std::string &line, Server &server);
void process_directive(const std::string &line, Location &location);
void process_line(const std::string &line, std::vector<Server> &servers);

struct pollfd create_pollfd(int sock_fd);
std::string read_file(const std::string &filename);

void get_request(int sockfd, Server server, const std::string &full_path);
void handle_method(int sockfd, Server server, const std::string &full_path, const std::string &method);

int execute_cgi(void);
int redirect_stdout(int pipefd[2]);
void handle_error(std::string message);
void read_output(int sockfd, int pipefd[2]);
void create_process(int sockfd, const std::string &query_string);

void handle_request(int sockfd, Server server);
void send_response(int sockfd, const std::string &response);
std::string parse_url(const std::string &url, const std::string &index);
void handle_conn(std::vector<struct pollfd> &fds, std::vector<Server> &servers);
std::string generate_response(const std::string &status, const std::string &file);

void start_server(int sockfd);
int create_server_socket(void);
void set_non_blocking(int sockfd);
void bind_socket(int sockfd, int port);

#endif
