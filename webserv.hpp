/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:57 by anlima            #+#    #+#             */
/*   Updated: 2024/04/17 18:11:18 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cerrno>
#include <map>
#include <fstream>
#include <sstream>
#include <string>

# define PORT 8080
# define BUFFER_SIZE 1024
# define RES "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Hello, World!</h1></body></html>\n"
# define HTML_EXT ".html"
# define CSS_EXT ".css"
# define JS_EXT ".js"
# define HTML_MIME "text/html"
# define CSS_MIME "text/css"
# define JS_MIME "application/javascript"
# define DEFAULT_MIME "application/octet-stream"
# define OK_HEADER "HTTP/1.1 200 OK\r\n"
# define CONTENT_TYPE "Content-Type: "
# define CONTENT_LEN "Content-Length: "
# define CLEAR "\033[0m"
# define PINK "\033[38;5;206m"
# define LAVENDER "\033[38;5;183m"
# define MINT "\033[38;5;121m"
# define PEACH "\033[38;5;223m"
# define SKYBLUE "\033[38;5;117m"
# define YELLOW "\033[38;5;226m"
# define HEART "♡"
# define FLOWER "❀"

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
