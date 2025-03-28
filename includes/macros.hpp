/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:19:47 by anlima            #+#    #+#             */
/*   Updated: 2025/03/27 18:59:55 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_HPP
#define MACROS_HPP

#include <arpa/inet.h>
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
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <typeinfo>
#include <unistd.h>
#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include <ctime>
#include <algorithm>

#define PORT 8080
#define BUFFER_SIZE 8192
#define ARGS_SIZE 8
#define RES                                                               \
    "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Hello, " \
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
#define GET_PORT "listen"
#define ERROR_PAGE "/error.html"
#define UPLOAD_FOLDER "../public/images"
#define CONTENT_HEADER "Content-Disposition: form-data;"
#define TIMEOUT 5000

typedef struct s_request
{
    std::string cgi;
    std::string url;
    std::string index;
    std::string method;
    std::string request;
    std::string filename;
    std::string path_info;
    std::string error_page;
    std::string image_data;
    std::string dir_listing;
    std::string allowed_methods;
} t_request;

#endif
