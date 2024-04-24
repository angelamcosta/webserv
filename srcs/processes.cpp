/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:43:18 by anlima            #+#    #+#             */
/*   Updated: 2024/04/24 17:26:17 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

int execute_cgi(void);
void create_process(int sockfd);
int redirect_stdout(int pipefd[2]);
void handle_error(std::string message);
void read_output(int sockfd, int pipefd[2]);

int execute_cgi(void) {
    char *args[] = {(char *)PYTHON_EXEC, (char *)PYTHON_INDEX, NULL};
    if (execve(PYTHON_EXEC, args, NULL) == -1) {
        handle_error("Error in executing Python cgi script");
        return (0);
    }
    return (1);
}

void create_process(int sockfd) {
    int pipefd[2];
    if (pipe(pipefd) == -1)
        throw std::runtime_error("Error in creating pipe");

    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        throw std::runtime_error("Error in forking process");
    }
    if (pid == 0) {
        close(pipefd[0]);
        if (!redirect_stdout(pipefd))
            throw std::runtime_error("Error");
        if (!execute_cgi())
            throw std::runtime_error("Error");
    } else {
        close(pipefd[1]);
        read_output(sockfd, pipefd);
    }
}

int redirect_stdout(int pipefd[2]) {
    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
        handle_error("Error in redirecting stdout");
        return (0);
    }
    close(pipefd[1]);
    return (1);
}

void handle_error(std::string message) {
    std::cout << PINK << message << CLEAR << std::endl;
}

void read_output(int sockfd, int pipefd[2]) {
    std::stringstream response;
    char temp_buff[BUFFER_SIZE];
    ssize_t bytes_read;
    while ((bytes_read = read(pipefd[0], temp_buff, BUFFER_SIZE)) > 0)
        response.write(temp_buff, bytes_read);
    close(pipefd[0]);
    std::string http_response = "HTTP/1.1 200 OK\r\n";
    http_response += "Content-Type: text/html\r\n";
    http_response += "\r\n";
    send(sockfd, http_response.c_str(), http_response.length(), 0);
    send(sockfd, response.str().c_str(), response.str().length(), 0);
}
