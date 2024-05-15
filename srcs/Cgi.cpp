/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:31:13 by anlima            #+#    #+#             */
/*   Updated: 2024/05/14 18:46:12 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cgi.hpp"
#include "../includes/Requests.hpp"

Cgi::Cgi(std::string url, std::string body, std::string method,
         std::string request, std::string filename, std::string file_path,
         std::string error_page)
    : _url(url), _body(body), _method(method), _request(request),
      _filename(filename), _file_path(file_path), _error_page(error_page) {
    handleMethods(method);
}

Cgi::~Cgi() {}

Cgi::Cgi(const Cgi &copy) {
    _url = copy._url;
    _body = copy._body;
    _method = copy._method;
    _filename = copy._filename;
    _file_path = copy._file_path;
    _error_page = copy._error_page;
}
Cgi &Cgi::operator=(const Cgi &copy) {
    if (this != &copy) {
        _url = copy._url;
        _body = copy._body;
        _method = copy._method;
        _filename = copy._filename;
        _file_path = copy._file_path;
        _error_page = copy._error_page;
    }
    return (*this);
}

const std::string &Cgi::getUrl(void) const { return (_url); }
const std::string &Cgi::getBody(void) const { return (_body); }
const std::string &Cgi::getMethod(void) const { return (_method); }
const std::string &Cgi::getFilename(void) const { return (_filename); }
const std::string &Cgi::getFilePath(void) const { return (_file_path); }
const std::string &Cgi::getErrorPage(void) const { return (_error_page); }

void Cgi::sendResponse(void) {
    std::string file = Requests::readFile(getFilePath().c_str());

    if (file == "") {
        file = Requests::readFile(getErrorPage().c_str());
        if (file == "") {
            std::string content =
                "<h1>ERROR: Could not find the specified file</h1>";
            std::cout << Requests::generateResponse("404 Not found", content)
                      << std::endl;
        }
        std::cout << Requests::generateResponse("404 Not found", file)
                  << std::endl;
        return;
    }

    std::cout << Requests::generateResponse("202 OK", file) << std::endl;
}

void Cgi::handleMethods(const std::string &method) {
    if (method == "GET")
        sendResponse();
    else if (method == "POST") {
        // handlePost();
        sendResponse();
    } else if (method == "PUT") {
        // handlePut();
        sendResponse();
    } else if (method == "DELETE") {
        // handleDelete();
        sendResponse();
    } else {
        std::string request, content;

        content = "<h1>Method not allowed</h1>";
        request = Requests::generateResponse("405 Not allowed", content);
        std::cout << request << std::endl;
    }
}
