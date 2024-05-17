/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:33:13 by anlima            #+#    #+#             */
/*   Updated: 2024/04/24 14:32:39 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Parser.hpp"

std::vector<Server> Parser::parseConf(const std::string &filename) {
    int flag = 0;
    std::ifstream file(filename.c_str());

    if (!file.is_open())
        throw std::invalid_argument("Error: Unable to open config file.");

    std::vector<Server> servers;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;
        processLine(line, servers, flag);
    }
    file.close();
    return (servers);
}

void Parser::processLocation(const std::string &line, Server &server) {
    std::istringstream iss(line);
    std::string location, path, signal;
    if (!(iss >> location >> path >> signal) || (signal != "{"))
        throw std::invalid_argument("Error: Invalid location directive.");
    server.addLocation(Location(path));
}

void Parser::processDirective(const std::string &line, Server &server) {
    std::istringstream iss(line);
    std::string name, value;
    if (!(iss >> name >> value))
        throw std::invalid_argument("Error: Invalid directive.");
    server.addDirective(Directive(name, value));
}

void Parser::processDirective(const std::string &line, Location &location) {
    std::istringstream iss(line);
    std::string name, value;
    if (!(iss >> name >> value))
        throw std::invalid_argument("Error: Invalid directive.");
    location.addDirective(Directive(name, value));
}

void Parser::processLine(const std::string &line, std::vector<Server> &servers,
                         int &flag) {
    std::istringstream iss(line);
    std::string token;

    if (!(iss >> token))
        return;
    if (token == "server" && !flag) {
        servers.push_back(Server());
        if ((iss >> token) && (token != "{"))
            throw std::invalid_argument("Error: Invalid server definition.");
    } else if (token == "server" && flag)
        throw std::invalid_argument("Error: Invalid server definition.");
    if (token == "{")
        flag++;
    else if (token == "location" && flag) {
        if (servers.empty())
            throw std::invalid_argument(
                "Error: Location block outside server block.");
        processLocation(line, servers.back());
        flag++;
    } else if (token != "}" && flag) {
        if (servers.empty())
            throw std::invalid_argument(
                "Error: Directive block outside server block.");

        Server &last_server = servers.back();
        const std::vector<Location> &locations = last_server.getLocations();
        if (!locations.empty()) {
            const Location &last_location = locations.back();
            processDirective(line, const_cast<Location &>(last_location));
        } else {
            processDirective(line, last_server);
        }
    } else if (token == "}")
        flag--;
}
