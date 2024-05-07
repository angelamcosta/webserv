/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:30:38 by anlima            #+#    #+#             */
/*   Updated: 2024/05/07 16:09:55 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

void get_request(int sockfd, Server server, const std::string &full_path);
void handle_method(int sockfd, Server server, const std::string &full_path, const std::string &method);

void get_request(int sockfd, Server server, const std::string &full_path) {
    std::string file = read_file(full_path);
    if (file == "" || file.empty()) {
        std::string file_error = read_file(server.getRoot() + ERROR_PAGE);
        if (file_error == "" || file_error.empty()) {
            std::string response = "HTTP/1.1 404 Not Found\r\n\r\n";
            send_response(sockfd, response);
            return;
        }
        std::string response = generate_response("200 OK", file_error);
        send_response(sockfd, response);
        return;
    }
    std::string response = generate_response("200 OK", file);
    send_response(sockfd, response);
}

void handle_method(int sockfd, Server server, const std::string &full_path, const std::string &method) {
    if (method == "GET")
        get_request(sockfd, server, full_path);
    // else if (method == "POST")
    //     get_request(sockfd, server, full_path);
    // else if (method == "PUT")
    //     get_request(sockfd, server, full_path);
    // else if (method == "DELETE")
    //     get_request(sockfd, server, full_path);
    else {
        std::string response = "HTTP/1.1 405 Method Not Allowed\r\n\r\n";
        send_response(sockfd, response);
    }
}

void post_request() {}

void put_request() {}

void delete_request() {}