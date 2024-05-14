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

Cgi::Cgi(std::string url, std::string method, std::string filename,
         std::string file_path, std::string error_page)
    : _url(url), _method(method), _filename(filename), _file_path(file_path),
      _error_page(error_page) {}

Cgi::~Cgi() {}

Cgi::Cgi(const Cgi &copy) {
    _url = copy._url;
    _method = copy._method;
    _filename = copy._filename;
    _file_path = copy._file_path;
    _error_page = copy._error_page;
}
Cgi &Cgi::operator=(const Cgi &copy) {
    if (this != &copy) {
        _url = copy._url;
        _method = copy._method;
        _filename = copy._filename;
        _file_path = copy._file_path;
        _error_page = copy._error_page;
    }
    return (*this);
}

const std::string &Cgi::getUrl(void) const { return (_url); }
const std::string &Cgi::getMethod(void) const { return (_method); }
const std::string &Cgi::getFilename(void) const { return (_filename); }
const std::string &Cgi::getFilePath(void) const { return (_file_path); }
const std::string &Cgi::getErrorPage(void) const { return (_error_page); }

void Cgi::readFile(void) {
    std::ifstream file(getFilePath().c_str());

    if (!file.is_open()) {
        std::ifstream error_file(getErrorPage().c_str());
        if (!error_file.is_open()) {
            std::string content =
                "<h1>ERROR: Could not find the specified file</h1>";
            std::cout << Requests::generate_response("404 Not found", content)
                      << std::endl;
        }
        std::ostringstream file_content;
        file_content << error_file.rdbuf();
        error_file.close();
        std::cout << Requests::generate_response("404 Not found",
                                                 file_content.str())
                  << std::endl;
        return;
    }

    std::ostringstream file_content;
    file_content << file.rdbuf();
    file.close();
    std::cout << Requests::generate_response("202 OK", file_content.str())
              << std::endl;
}
