/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:33:13 by anlima            #+#    #+#             */
/*   Updated: 2024/08/26 17:14:28 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Parser.hpp"

// TODO - : Make parser sturdier! Change config logic

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
    if (flag)
        throw std::invalid_argument("Error: Invalid server definition.");
    file.close();
    checkServers(servers);
    return (servers);
}

void Parser::processLocation(const std::string &line, Server &server) {
    std::stringstream iss(line);
    std::string location, path, signal;
    if (!(iss >> location >> path >> signal) || (signal != "{"))
        throw std::invalid_argument("Error: Invalid location directive.");
    server.addLocation(Location(path));
}

void Parser::processDirective(const std::string &line, Server &server) {
    std::stringstream iss(line);
    std::string name, value;

    if (!(iss >> name))
        throw std::invalid_argument("Error: Invalid directive.");
    std::getline(iss, value);
    value = trim(value);
    server.addDirective(Directive(trim(name), trim(value)));
}

void Parser::processDirective(const std::string &line, Location &location) {
    std::stringstream iss(line);
    std::string name, value;

    if (!(iss >> name))
        throw std::invalid_argument("Error: Invalid directive.");
    std::getline(iss, value);
    location.addDirective(Directive(trim(name), trim(value)));
}

// TODO - : Handle { } 

void Parser::processLine(const std::string &line, std::vector<Server> &servers,
                         int &flag) {
    std::stringstream iss(line);
    std::string token;

    if (!(iss >> token))
        return;
    if (token == "server" && !flag) {
        if (((!(iss >> token)) || token != "{"))
            throw std::invalid_argument("Error: Invalid server definition.");
        servers.push_back(Server());
    }
    if (token == "{" && (iss >> token))
        throw std::invalid_argument("Error: Invalid server definition.");
    else if (token == "{")
        flag++;
    else if (token == "}" && (iss >> token))
        throw std::invalid_argument("Error: Invalid server definition.");
    else if (token == "location" && flag) {
        if (servers.empty())
            throw std::invalid_argument(
                "Error: Location block outside server block.");
        processLocation(line, servers.back());
        flag++;
    }
    else if (token != "}" && flag) {
        if (servers.empty())
            throw std::invalid_argument("Error: Directive block outside server block.");
        Server &last_server = servers.back();
        const std::vector<Location> &locations = last_server.getLocations();
        if (!locations.empty()) {
            const Location &last_location = locations.back();
            processDirective(line, const_cast<Location &>(last_location));
        }
        else
            processDirective(line, last_server);
    }
    else if (token == "}")
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

void Parser::checkServers(std::vector<Server> &servers) {
    for (size_t i = 0; i < servers.size(); ++i) {
        std::string server_name1 = servers[i].getServerName();
        std::string host1 = servers[i].getPort();
        for (size_t j = 0; j < servers.size(); ++j) {
            std::string server_name2 = servers[j].getServerName();
            std::string host2 = servers[j].getPort();
            if (i == j)
                continue ;
            if (server_name1 == server_name2 && host1 == host2)
                throw std::invalid_argument("Error: Two different servers share the same server name and port.");
        }
    }
}
