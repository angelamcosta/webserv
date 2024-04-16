/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:57 by anlima            #+#    #+#             */
/*   Updated: 2024/04/16 19:11:57 by anlima           ###   ########.fr       */
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

void        create_process(int server_socket, int client_socket);

void        handle_request(int sockfd);

int         bind_socket(int sockfd);
int         start_server(int sockfd);
int         create_server_socket(void);

std::string mime_type(void);
void        serve_file(int client_socket, std::string const &file_path);

#endif
