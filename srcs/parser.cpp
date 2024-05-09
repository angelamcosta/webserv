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

std::vector<Server> Parser::parse_conf(const std::string &filename) {
    std::ifstream file(filename.c_str());

    if (!file.is_open())
        throw std::invalid_argument("Error: Unable to open config file.");

    std::vector<Server> servers;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;
        process_line(line, servers);
    }
    file.close();
    return (servers);
}

void Parser::process_location(const std::string &line, Server &server) {
    std::istringstream iss(line);
    std::string location, path;
    if (!(iss >> location >> path))
        throw std::invalid_argument("Error: Invalid location directive.");
    server.addLocation(Location(path));
}

void Parser::process_directive(const std::string &line, Server &server) {
    std::istringstream iss(line);
    std::string name, value;
    if (!(iss >> name >> value))
        throw std::invalid_argument("Error: Invalid directive.");
    server.addDirective(Directive(name, value));
}

void Parser::process_directive(const std::string &line, Location &location) {
    std::istringstream iss(line);
    std::string name, value;
    if (!(iss >> name >> value))
        throw std::invalid_argument("Error: Invalid directive.");
    location.addDirective(Directive(name, value));
}

void Parser::process_line(const std::string &line, std::vector<Server> &servers) {
    std::istringstream iss(line);
    std::string token;
    if (!(iss >> token))
        return;

    if (token == "server")
        servers.push_back(Server());
    else if (token == "location") {
        if (servers.empty())
            throw std::invalid_argument(
                "Error: Location block outside server block.");
        process_location(line, servers.back());
    } else if (token != "}") {
        if (servers.empty())
            throw std::invalid_argument(
                "Error: Directive block outside server block.");

        Server &last_server = servers.back();
        const std::vector<Location> &locations = last_server.getLocations();
        if (!locations.empty()) {
            const Location &last_location = locations.back();
            process_directive(line, const_cast<Location &>(last_location));
        } else {
            process_directive(line, last_server);
        }
    }
}
