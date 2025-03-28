/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Processes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:43:18 by anlima            #+#    #+#             */
/*   Updated: 2025/03/27 12:04:44 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Utils.hpp"
#include "../includes/Parser.hpp"
#include "../includes/Requests.hpp"
#include "../includes/Processes.hpp"

int Processes::executeCgi(std::string cgi)
{
    std::vector<char *> args;

    args.push_back(const_cast<char *>(cgi.c_str()));
    args.push_back(NULL);
    if (execve(cgi.c_str(), args.data(), NULL) == -1)
        return (0);
    return (1);
}

int Processes::redirectStdout(int pipefd[2])
{
    if (dup2(pipefd[1], STDOUT_FILENO) == -1)
    {
        handleError("Error in redirecting stdout");
        return (0);
    }
    close(pipefd[1]);
    return (1);
}

int Processes::redirectStdin(int pipefd[2])
{
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
    {
        handleError("Error in redirecting stdin");
        return (0);
    }
    close(pipefd[0]);
    return (1);
}

void Processes::handleError(std::string message)
{
    std::cout << message << std::endl;
}

std::string Processes::readOutput(int pipefd[2])
{
    ssize_t bytes_read;
    char temp_buff[BUFFER_SIZE];
    std::ostringstream http_response;

    while ((bytes_read = read(pipefd[0], temp_buff, BUFFER_SIZE)) > 0)
        http_response.write(temp_buff, bytes_read);
    if (bytes_read < 0)
        perror("read");
    close(pipefd[0]);
    return (http_response.str());
}

void Processes::writeInput(int pipefd[2], const t_request &data)
{
    std::ostringstream input_stream;

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

std::string Processes::createProcess(const t_request &data)
{
    int stdin_pipefd[2];
    int stdout_pipefd[2];
    std::string response;

    if (pipe(stdout_pipefd) == -1 || pipe(stdin_pipefd) == -1)
        throw std::runtime_error("Error in creating pipe");
    pid_t pid = fork();
    if (pid == -1)
    {
        close(stdout_pipefd[0]);
        close(stdout_pipefd[1]);
        close(stdin_pipefd[0]);
        close(stdin_pipefd[1]);
        throw std::runtime_error("Error in forking process");
    }
    if (pid == 0)
    {
        close(stdout_pipefd[0]);
        close(stdin_pipefd[1]);
        if (!redirectStdout(stdout_pipefd))
            throw std::runtime_error("Error in redirecting stdout");
        if (data.cgi.empty())
        {
            Utils utils(data);
            if (data.method == "invalid_size")
                utils.handleMethod(data.method);
            else
                utils.handleMethod("");
        }
        else
        {
            if (!redirectStdin(stdin_pipefd))
                throw std::runtime_error("Error in redirecting stdin");
            else if (!data.cgi.empty() && (!executeCgi(Parser::trim(data.cgi))))
                throw std::runtime_error("Error in executing CGI script; path => " + data.cgi);
        }
        throw std::runtime_error("");
    }
    else
    {
        close(stdout_pipefd[1]);
        close(stdin_pipefd[0]);
        if (!data.cgi.empty())
            writeInput(stdin_pipefd, data);
        response = readOutput(stdout_pipefd);
        int status;
        waitpid(pid, &status, 0);
		close(stdout_pipefd[0]);
        close(stdin_pipefd[1]);
    }
    return (response);
}
