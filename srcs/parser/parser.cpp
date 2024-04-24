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

#include "../../includes/webserv.hpp"

std::vector<Server> parse_conf(std::string filename);
void process_location(const std::string &line, Server &server);
void process_directive(const std::string &line, Server &server);
void process_directive(const std::string &line, Location &location);
void process_line(const std::string &line, std::vector<Server> &servers);

std::vector<Server> parse_conf(std::string filename) {
    std::ifstream file(filename.c_str());

    if (!file.is_open())
        throw std::invalid_argument("Error: Unable to open config file.");

    std::vector<Server> servers;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        process_line(line, servers);
    }
    return (servers);
}

void process_location(const std::string &line, Server &server) {
    std::istringstream iss(line);
    std::string location, path;
    iss >> location >> path;

    server.addLocation(Location(path));
}

void process_directive(const std::string &line, Server &server) {
    std::istringstream iss(line);
    std::string name, value;
    iss >> name >> value;

    server.addDirective(Directive(name, value));
}

void process_directive(const std::string &line, Location &location) {
    std::istringstream iss(line);
    std::string name, value;
    iss >> name >> value;

    location.addDirective(Directive(name, value));
}

void process_line(const std::string &line, std::vector<Server> &servers) {
    std::istringstream iss(line);
    std::string token;
    iss >> token;

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
        if (servers.back().getLocations().empty())
            process_directive(line, servers.back());
        else
            process_directive(line, servers.back().getLocations().back());
    }
}
