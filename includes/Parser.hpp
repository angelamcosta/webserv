/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:58:47 by anlima            #+#    #+#             */
/*   Updated: 2024/05/09 17:14:22 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include "Server.hpp"
#include "macros.hpp"

class Parser {
  private:
    Parser();

  public:
    static std::vector<Server> parse_conf(const std::string &filename);
    static void process_location(const std::string &line, Server &server);
    static void process_directive(const std::string &line, Server &server);
    static void process_directive(const std::string &line, Location &location);
    static void process_line(const std::string &line,
                             std::vector<Server> &servers);
};

#endif
