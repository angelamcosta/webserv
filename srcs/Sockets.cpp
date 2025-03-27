/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sockets.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:54:32 by anlima            #+#    #+#             */
/*   Updated: 2025/03/27 15:44:34 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Sockets.hpp"

int Sockets::createServer(const std::string &serverName,
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

    int sockfd;
    std::stringstream portsStream(port.c_str());
    std::string singlePort;
    
    portsStream >> singlePort;
    for (std::vector<std::string>::iterator it = name.begin(); it != name.end(); ++it) {
        int status = getaddrinfo((*it).c_str(), singlePort.c_str(), &hints, &res);
        if (status != 0)
            throw std::runtime_error("getaddrinfo error");
        sockfd = createSocket(res);
        bindSocket(sockfd, res);
        startServer(sockfd, res);
        freeaddrinfo(res);
        setNonBlocking(sockfd);
    }
    return (sockfd);
}

int Sockets::createSocket(struct addrinfo *res) {
    int opt = 1;
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (sockfd < 0) {
        perror("socket failed");
        freeaddrinfo(res);
        throw std::runtime_error("socket creation failed");
    }

    struct timeval timeout;
    timeout.tv_sec = 30;
    timeout.tv_usec = 0;

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout))) {
        perror("socket failed");
        close(sockfd);
        freeaddrinfo(res);
        throw std::runtime_error("socket creation failed");
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE | SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("socket failed");
        close(sockfd);
        freeaddrinfo(res);
        throw std::runtime_error("socket creation failed");
    }

    int idle = 60;
    int interval = 10;
    int count = 5;

    setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPIDLE, &idle, sizeof(idle));
    setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(interval));
    setsockopt(sockfd, IPPROTO_TCP, TCP_KEEPCNT, &count, sizeof(count));

    return (sockfd);
}

void Sockets::startServer(int sockfd, struct addrinfo *res) {
    if (listen(sockfd, MAX_CONN) < 0) {
        close(sockfd);
        freeaddrinfo(res);
        perror("listen");
        throw std::runtime_error("socket listen failed");
    }
}

void Sockets::setNonBlocking(int sockfd) {
    if (fcntl(sockfd, F_SETFL, O_NONBLOCK | FD_CLOEXEC) == -1) {
        perror("fcntl");
        throw std::runtime_error("socket set non blocking failed");
    }
}

void Sockets::bindSocket(int sockfd, struct addrinfo *res) {
    int bind_res = bind(sockfd, res->ai_addr, res->ai_addrlen);

    if (bind_res < 0) {
        close(sockfd);
        freeaddrinfo(res);
        perror("bind failed");
        throw std::runtime_error("bind failed");
    }
}
