/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_funcs.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:31:01 by anlima            #+#    #+#             */
/*   Updated: 2024/05/07 14:24:50 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

struct pollfd create_pollfd(int sock_fd);
std::string read_file(const std::string &filename);

struct pollfd create_pollfd(int sock_fd) {
    struct pollfd sock_pollfd;
    sock_pollfd.fd = sock_fd;
    sock_pollfd.events = POLLIN;
    sock_pollfd.revents = 0;
    return (sock_pollfd);
}

std::string read_file(const std::string &filename) {
    std::ifstream file(filename.c_str(), std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    std::ostringstream file_content;
    file_content << file.rdbuf();
    file.close();
    return (file_content.str());
}
