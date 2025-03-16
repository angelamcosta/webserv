/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:58:47 by anlima            #+#    #+#             */
/*   Updated: 2025/03/16 17:18:27 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include "Server.hpp"
#include "macros.hpp"
#include "Stack.hpp"

class Parser
{
private:
	Parser();

public:
	static int isValidConf(const std::string &name);
	static std::vector<Server> parseConf(const std::string &filename);
	static void processLocation(const std::string &line, Server &server, Stack &stack);
	static void processLocation(const std::string &line, Location &location, Stack &stack);
	static void processDirective(const std::string &line, Server &server);
	static void processDirective(const std::string &line, Location &location, Server &server);
	static void processLine(std::vector<std::string>, int i, std::vector<Server> &servers, int &flag, Stack &stack);
	static std::string trim(const std::string &str);
	static void checkServers(std::vector<Server> &servers);
	static void checkEmptyLoc(std::vector<std::string> lines, int i, int flag);
};

#endif