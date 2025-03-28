/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sockets.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:54:32 by anlima            #+#    #+#             */
/*   Updated: 2025/03/27 19:08:03 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Sockets.hpp"

std::vector<int> Sockets::createServer(const std::string &serverName,
                          const std::string &port) {
    struct addrinfo hints, *res;
    std::vector<std::string> name;
    std::stringstream iss(serverName);
    std::string value;

    if (serverName.empty())
        name.push_back("localhost");
    else {
        while (iss >> value)
            name.push_back(value);
    }

    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;

    std::vector<int> sockets;
    std::stringstream portsStream(port.c_str());
    std::string singlePort;

    while (portsStream >> singlePort) {
        for (std::vector<std::string>::iterator it = name.begin() ; it != name.end(); ++it) {
            int status = getaddrinfo((*it).c_str(), singlePort.c_str(), &hints, &res);
            if (status != 0)
                throw std::runtime_error("getaddrinfo error");
            int sockfd = createSocket(res);
            bindSocket(sockfd, res);
            startServer(sockfd, res);
            freeaddrinfo(res);
            setNonBlocking(sockfd);
            sockets.push_back(sockfd);
        }
    }
    std::cout << "Listening on port " << singlePort << std::endl;
    return (sockets);
}

int Sockets::createSocket(struct addrinfo *res) {
    int opt = 1;
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (sockfd < 0) {
        perror("socket failed");
        freeaddrinfo(res);
        exit(EXIT_FAILURE);
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        close(sockfd);
        freeaddrinfo(res);
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    return (sockfd);
}

void Sockets::startServer(int sockfd, struct addrinfo *res) {
    if (listen(sockfd, SOMAXCONN) < 0) {
        close(sockfd);
        freeaddrinfo(res);
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

void Sockets::setNonBlocking(int sockfd) {
    if (fcntl(sockfd, F_SETFL, O_NONBLOCK) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
}

void Sockets::bindSocket(int sockfd, struct addrinfo *res) {
    int bind_res = bind(sockfd, res->ai_addr, res->ai_addrlen);

    if (bind_res < 0) {
        close(sockfd);
        freeaddrinfo(res);
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

struct pollfd Sockets::createPollfd(int sock_fd) {
    struct pollfd sock_pollfd;

    sock_pollfd.fd = sock_fd;
    sock_pollfd.events = POLLIN | POLLOUT;;
    sock_pollfd.revents = 0;
    return (sock_pollfd);
}
