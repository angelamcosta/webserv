/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:19:47 by anlima            #+#    #+#             */
/*   Updated: 2024/05/15 15:56:20 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_HPP
#define MACROS_HPP

#include <arpa/inet.h>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <map>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#define PORT 8080
#define BUFFER_SIZE 1024
#define RES                                                                    \
    "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Hello, "      \
    "World!</h1></body></html>\n"
#define HTML_EXT ".html"
#define CSS_EXT ".css"
#define JS_EXT ".js"
#define HTML_MIME "text/html"
#define CSS_MIME "text/css"
#define JS_MIME "application/javascript"
#define DEFAULT_MIME "application/octet-stream"
#define OK_HEADER "HTTP/1.1 200 OK\r\n"
#define CONTENT_TYPE "Content-Type: "
#define CONTENT_LEN "Content-Length: "
#define CLEAR "\033[0m"
#define PINK "\033[38;5;206m"
#define LAVENDER "\033[38;5;183m"
#define MINT "\033[38;5;121m"
#define PEACH "\033[38;5;223m"
#define SKYBLUE "\033[38;5;117m"
#define YELLOW "\033[38;5;226m"
#define HEART "♡"
#define FLOWER "❀"
#define PYTHON_EXEC "/usr/bin/python3"
#define PYTHON_INDEX "/home/anlima/webserv/cgi-bin/script.py"
#define PERL_EXEC "/usr/bin/perl"
#define PERL_INDEX "/home/anlima/webserv/cgi-bin/script.pl"
#define CPP_EXEC "/usr/bin/g++"
#define CPP_INDEX "/home/anlima/webserv/cgi-bin/script"
#define GET_PORT "listen"
#define ERROR_PAGE "/error.html"
#define HTTP_GET "GET"
#define HTTP_POST "POST"
#define HTTP_PUT "PUT"
#define HTTP_DELETE "DELETE"
#define UPLOAD_FOLDER "/home/anlima/webserv/public/images"
#define CONTENT_HEADER "Content-Disposition: form-data;"
#define TIMEOUT 5000

typedef struct s_request {
    std::string url;
    std::string body;
    std::string method;
    std::string request;
    std::string filename;
    std::string full_path;
    std::string error_page;
    std::string allowed_methods;
} t_request;

#endif
