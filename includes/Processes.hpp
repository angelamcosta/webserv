/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Processes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:17:50 by anlima            #+#    #+#             */
/*   Updated: 2024/05/15 20:19:39 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSES_HPP
#define PROCESSES_HPP

#include "macros.hpp"

class Processes {
  private:
    Processes();

  public:
    static int executeCgi(const t_request &data);
    static int redirectStdout(int pipefd[2]);
    static void handleError(std::string message);
    static void readOutput(int sockfd, int pipefd[2]);
    static void createProcess(int sockfd, const t_request &data);
    static std::vector<char *> getArgs(const t_request &data);
};

#endif