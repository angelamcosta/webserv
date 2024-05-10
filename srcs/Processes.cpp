/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Processes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:43:18 by anlima            #+#    #+#             */
/*   Updated: 2024/05/10 16:49:29 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Processes.hpp"
#include "../includes/Requests.hpp"

int Processes::execute_cgi(const t_request &data) {
    std::vector<char *> args = get_args(data);
    
    if (execve(PYTHON_EXEC, args.data(), NULL) == -1) {
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
    std::string response = Requests::generate_response("200 OK", http_response.str());
    Requests::send_response(sockfd, response);
}

void Processes::create_process(int sockfd, const t_request &data) {
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
        
        if (!redirect_stdout(pipefd))
            throw std::runtime_error("Error");
        if (!execute_cgi(data))
            throw std::runtime_error("Error");
    } else {
        close(pipefd[1]);
        read_output(sockfd, pipefd);
    }
}

std::vector<char *> Processes::get_args(const t_request &data) {
    std::vector<char *> args;
    
    args.push_back(const_cast<char*>(PYTHON_EXEC));
    args.push_back(const_cast<char*>(PYTHON_INDEX));
    args.push_back(const_cast<char*>(data.url.c_str()));
    args.push_back(const_cast<char*>(data.method.c_str()));
    args.push_back(const_cast<char*>(data.filename.c_str()));
    args.push_back(const_cast<char*>(data.full_path.c_str()));
    args.push_back(const_cast<char*>(data.error_page.c_str()));
    args.push_back(NULL);

    return (args);
}
