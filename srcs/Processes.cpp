/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Processes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:43:18 by anlima            #+#    #+#             */
/*   Updated: 2024/06/04 18:48:10 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Processes.hpp"
#include "../includes/Requests.hpp"

int Processes::executeCgi(void) {
    std::vector<char *> args;
    args.push_back(const_cast<char *>(PYTHON_INDEX));
    args.push_back(NULL);

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

int Processes::redirectStdin(int pipefd[2]) {
    if (dup2(pipefd[0], STDIN_FILENO) == -1) {
        handleError("Error in redirecting stdin");
        return (0);
    }
    close(pipefd[0]);
    return (1);
}

void Processes::handleError(std::string message) {
    std::cout << message << std::endl;
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

void Processes::writeInput(int pipefd[2], const t_request &data) {
    std::stringstream input_stream;

    input_stream << data.url << "\n";
    input_stream << data.index << "\n";
    input_stream << data.method << "\n";
    input_stream << data.path_info << "\n";
    input_stream << data.error_page << "\n";
    input_stream << data.dir_listing << "\n";
    input_stream << data.allowed_methods << "\n";
    input_stream << data.image_data << "\n";
    input_stream << data.filename << "\n";

    std::string input_data = input_stream.str();
    write(pipefd[1], input_data.c_str(), input_data.size());
    close(pipefd[1]);
}

void Processes::createProcess(int sockfd, const t_request &data) {
    int stdout_pipefd[2];
    int stdin_pipefd[2];

    if (pipe(stdout_pipefd) == -1 || pipe(stdin_pipefd) == -1)
        throw std::runtime_error("Error in creating pipe");

    pid_t pid = fork();
    if (pid == -1) {
        close(stdout_pipefd[0]);
        close(stdout_pipefd[1]);
        close(stdin_pipefd[0]);
        close(stdin_pipefd[1]);
        throw std::runtime_error("Error in forking process");
    }
    if (pid == 0) {
        close(stdout_pipefd[0]);
        close(stdin_pipefd[1]);
        close(sockfd);
        if (!redirectStdout(stdout_pipefd) || !redirectStdin(stdin_pipefd))
            throw std::runtime_error("Error");
        if (!executeCgi())
            throw std::runtime_error("Error");
    } else {
        close(stdout_pipefd[1]);
        close(stdin_pipefd[0]);
        writeInput(stdin_pipefd, data);
        readOutput(sockfd, stdout_pipefd);
    }
}
