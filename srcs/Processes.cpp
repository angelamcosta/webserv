/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Processes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:43:18 by anlima            #+#    #+#             */
/*   Updated: 2024/05/27 16:39:32 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Processes.hpp"
#include "../includes/Requests.hpp"

int Processes::executeCgi(const t_request &data) {
    std::vector<char *> args = getArgs(data);

    if (execve(PYTHON_INDEX, args.data(), NULL) == -1) {
        handleError("Error in executing cgi script");
        return (0);
    }
    return (1);
}

int Processes::redirectStdout(int pipefd[2]) {
    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
        handleError("Error in redirecting stdout");
        return (0);
    }
    close(pipefd[1]);
    return (1);
}

void Processes::handleError(std::string message) {
    std::cout << PINK << message << CLEAR << std::endl;
}

void Processes::readOutput(int sockfd, int pipefd[2]) {
    std::stringstream http_response;
    char temp_buff[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(pipefd[0], temp_buff, BUFFER_SIZE)) > 0)
        http_response.write(temp_buff, bytes_read);
    if (bytes_read < 0) {
        perror("read");
        close(pipefd[0]);
        return;
    }
    close(pipefd[0]);
    Requests::sendResponse(sockfd, http_response.str());
}

void Processes::createProcess(int sockfd, const t_request &data) {
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
        if (!redirectStdout(pipefd))
            throw std::runtime_error("Error");
        if (!executeCgi(data))
            throw std::runtime_error("Error");
    } else {
        close(pipefd[1]);
        readOutput(sockfd, pipefd);
    }
}

std::vector<char *> Processes::getArgs(const t_request &data) {
    std::vector<char *> args;

    args.push_back(const_cast<char *>(PYTHON_INDEX));
    args.push_back(const_cast<char *>(data.url.c_str()));
    args.push_back(const_cast<char *>(data.index.c_str()));
    args.push_back(const_cast<char *>(data.method.c_str()));
    args.push_back(const_cast<char *>(data.path_info.c_str()));
    args.push_back(const_cast<char *>(data.error_page.c_str()));
    args.push_back(const_cast<char *>(data.dir_listing.c_str()));
    args.push_back(const_cast<char *>(data.allowed_methods.c_str()));
    args.push_back(const_cast<char *>(data.image_data.c_str()));
    args.push_back(const_cast<char *>(data.filename.c_str()));
    args.push_back(NULL);

    return (args);
}
