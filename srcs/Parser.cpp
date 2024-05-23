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

    if (!(iss >> name))
        throw std::invalid_argument("Error: Invalid directive.");
    std::getline(iss, value);
    value = trim(value);
    server.addDirective(Directive(trim(name), trim(value)));
}

void Parser::processDirective(const std::string &line, Location &location) {
    std::istringstream iss(line);
    std::string name, value;

    if (!(iss >> name))
        throw std::invalid_argument("Error: Invalid directive.");
    std::getline(iss, value);
    location.addDirective(Directive(trim(name), trim(value)));
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

std::string Parser::trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return (str.substr(first, (last - first + 1)));
}
