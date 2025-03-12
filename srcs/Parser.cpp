/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:33:13 by anlima            #+#    #+#             */
/*   Updated: 2025/02/21 12:53:06 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Parser.hpp"

int Parser::isValidConf(const std::string &name) {
    std::string args[] = {"listen", "root", "index", "client_max_body_size", "autoindex", "allow_methods", "cgi_path", "error_page"};
    for (size_t i = 0; i < ARGS_SIZE; ++i) {
        if (name == args[i])
            return (1);
    }
    return (0);
}

std::vector<Server> Parser::parseConf(const std::string &filename) {
    int flag = 0;
    std::ifstream file(filename.c_str());
    Stack   stack = Stack();

    if (!file.is_open())
        throw std::invalid_argument("Error: Unable to open config file.");

    std::vector<Server> servers;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;
        processLine(line, servers, flag, stack);
    }
    if (flag)
        throw std::invalid_argument("Error: Invalid server definition.");
    file.close();
    checkServers(servers);
    return (servers);
}

void Parser::processLocation(const std::string &line, Server &server, Stack &stack) {
    std::stringstream iss(line);
    std::string location, path, signal;
    if (!(iss >> location >> path >> signal) || (signal != "{"))
        throw std::invalid_argument("Error: Invalid location directive.");
    Location return_location = Location(trim(path));
    stack.addToStack(return_location);
    server.addLocation(return_location);
}

void Parser::processLocation(const std::string &line, Location &location, Stack &stack) {
    std::stringstream iss(line);
    std::string new_location, path, signal;
    if (!(iss >> new_location >> path >> signal) || (signal != "{"))
        throw std::invalid_argument("Error: Invalid location directive.");
    Location return_location = Location(trim(path));
    stack.addToStack(return_location);
    location.addLocation(return_location);
}

void Parser::processDirective(const std::string &line, Server &server) {
    std::stringstream iss(line);
    std::string name, value;

    if (!(iss >> name))
        throw std::invalid_argument("Error: Invalid directive.");
    if (name != "listen" && server.checkDirectives(trim(name)))
        throw std::invalid_argument("Error: Invalid directive.");
    std::getline(iss, value);
    value = trim(value);
    server.addDirective(Directive(trim(name), trim(value)));
}

void Parser::processDirective(const std::string &line, Location &location, Server &server) {
    std::stringstream iss(line);
    std::string name, value;

    if (!(iss >> name))
        throw std::invalid_argument("Error: Invalid directive.");
    if (name != "listen" && location.checkDirectives(trim(name)))
        throw std::invalid_argument("Error: Invalid directive.");
    if (name == "allow_methods" && !(location.getPath().empty()))
        server.addUrlMethod(trim(line), location.getPath());
    if (name == "cgi_path") {
        std::getline(iss, value);
        server.setCgi(value); 
    }
    else if (isValidConf(name)) {
        std::getline(iss, value);
        location.addDirective(Directive(trim(name), trim(value)));
    }
    else
        throw std::invalid_argument("Error: Invalid directive.");
}

void Parser::processLine(const std::string &line, std::vector<Server> &servers, int &flag, Stack &stack) {
    std::stringstream iss(line);
    std::string token;

    if (!(iss >> token))
        return;
    if (token == "server" && !flag) {
        if (((!(iss >> token)) || token != "{"))
            throw std::invalid_argument("Error: Invalid server definition.");
        servers.push_back(Server());
        stack.addToStack();
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
        if (!stack.getType())
            processLocation(line, servers.back(), stack);
        else
            processLocation(line, stack.getLocation(), stack);
        flag++;
    }
    else if (token != "}" && flag) {
        if (servers.empty())
            throw std::invalid_argument("Error: Directive block outside server block.");
        if (stack.getType())
            processDirective(line, stack.getLocation(),servers.back());
        else
            processDirective(line, servers.back());
    }
    else if (token == "}") {
        stack.remove();
        flag--;
    }
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
