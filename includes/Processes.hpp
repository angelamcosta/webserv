/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Processes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:17:50 by anlima            #+#    #+#             */
/*   Updated: 2024/06/06 15:44:26 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSES_HPP
#define PROCESSES_HPP

#include "macros.hpp"

class Processes {
  private:
    Processes();

  public:
    static int executeCgi(void);
    static int redirectStdin(int pipefd[2]);
    static int redirectStdout(int pipefd[2]);
    static void handleError(std::string message);
    static std::string readOutput(int pipefd[2]);
    static std::string createProcess(const t_request &data);
    static std::vector<char *> getArgs(const t_request &data);
    static void writeInput(int pipefd[2], const t_request &data);
};

#endif