/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:58:47 by anlima            #+#    #+#             */
/*   Updated: 2024/05/21 16:05:48 by anlima           ###   ########.fr       */
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
    static std::vector<Server> parseConf(const std::string &filename);
    static void processLocation(const std::string &line, Server &server);
    static void processDirective(const std::string &line, Server &server);
    static void processDirective(const std::string &line, Location &location);
    static void processLine(const std::string &line, std::vector<Server> &servers, int &flag);
    static std::string trim(const std::string &str);
};

#endif
