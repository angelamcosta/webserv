/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Processes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:17:50 by anlima            #+#    #+#             */
/*   Updated: 2024/05/10 16:35:53 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSES_HPP
#define PROCESSES_HPP

#include "macros.hpp"

class Processes {
  private:
    Processes();

  public:
    static int execute_cgi(const t_request &data);
    static int redirect_stdout(int pipefd[2]);
    static void handle_error(std::string message);
    static void read_output(int sockfd, int pipefd[2]);
    static void create_process(int sockfd, const t_request &data);
    static std::vector<char *> get_args(const t_request &data);
};

#endif