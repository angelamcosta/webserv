/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva <gsilva@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:58:47 by anlima            #+#    #+#             */
/*   Updated: 2025/02/12 16:18:08 by gsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include "Server.hpp"
#include "macros.hpp"
#include "Stack.hpp"

class Parser {
  private:
    Parser();

  public:
    static std::vector<Server> parseConf(const std::string &filename);
    static void processLocation(const std::string &line, Server &server, Stack &stack);
	static void processLocation(const std::string &line, Location &location, Stack &stack);
    static void processDirective(const std::string &line, Server &server);
    static void processDirective(const std::string &line, Location &location, Server &server);
    static void processLine(const std::string &line, std::vector<Server> &servers, int &flag, Stack &stack);
    static std::string trim(const std::string &str);
    static void checkServers(std::vector<Server> &servers);
};

#endif
