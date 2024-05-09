/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Processes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:43:18 by anlima            #+#    #+#             */
/*   Updated: 2024/05/09 17:42:27 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Processes.hpp"

int Processes::execute_cgi(void) {
    char *args[] = {(char *)PYTHON_EXEC, (char *)PYTHON_INDEX, NULL};
    if (execve(PYTHON_EXEC, args, NULL) == -1) {
        handle_error("Error in executing Python cgi script");
        return (0);
    }
    return (1);
}

int Processes::redirect_stdout(int pipefd[2]) {
    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
        handle_error("Error in redirecting stdout");
        return (0);
    }
    close(pipefd[1]);
    return (1);
}

void Processes::handle_error(std::string message) {
    std::cout << PINK << message << CLEAR << std::endl;
}

void Processes::read_output(int sockfd, int pipefd[2]) {
    std::stringstream response;
    char temp_buff[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(pipefd[0], temp_buff, BUFFER_SIZE)) > 0)
        response.write(temp_buff, bytes_read);
    if (bytes_read < 0) {
        perror("read");
        close(pipefd[0]);
        return;
    }
    close(pipefd[0]);
    std::string http_response = "HTTP/1.1 200 OK\r\n";
    http_response += "Content-Type: text/html\r\n";
    http_response += "\r\n";
    http_response += response.str();
    send(sockfd, http_response.c_str(), http_response.length(), 0);
}

void Processes::create_process(int sockfd, const std::string &query_string) {
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
        close(sockfd);
        setenv("QUERY_STRING", query_string.c_str(), 1);
        if (!redirect_stdout(pipefd))
            throw std::runtime_error("Error");
        if (!execute_cgi())
            throw std::runtime_error("Error");
    } else {
        close(pipefd[1]);
        read_output(sockfd, pipefd);
    }
}
