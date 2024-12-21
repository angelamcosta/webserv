/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:31:13 by anlima            #+#    #+#             */
/*   Updated: 2024/10/22 16:09:23 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cgi.hpp"
#include "../includes/Requests.hpp"

Cgi::~Cgi() {}

Cgi::Cgi(const s_request &data) : _data(data), _url(""), _full_path(""), _upload_dir(""), _error_path("")
{ }

Cgi::Cgi(const Cgi &copy)
{
    if (this != &copy) {
        _data = copy._data;
        _url = copy._url;
        _full_path = copy._full_path;
        _upload_dir = copy._upload_dir;
        _error_path = copy._error_path;
    }
}

Cgi &Cgi::operator=(const Cgi &copy)
{
    if (this != &copy) {
        _data = copy._data;
        _url = copy._url;
        _full_path = copy._full_path;
        _upload_dir = copy._upload_dir;
        _error_path = copy._error_path;
    }
    return (*this);
}

const s_request &Cgi::getData(void) { return (_data); }

const std::string &Cgi::getUrl(void) { return (_url); }
void Cgi::setUrl(void)
{
    _url = (_data.url == "/") ? '/' + _data.index : _data.index;
}

const std::string &Cgi::getFullPath(void) { return (_full_path); }
void Cgi::setFullPath(void) {
    if (!_url.empty() && _url.front() == '/' && !_data.path_info.empty() && _data.path_info.back() == '/')
        _full_path = _data.path_info + _url.substr(1);
    else if ((!_url.empty() && _url.front() == '/') || (!_data.path_info.empty() && _data.path_info.back() == '/'))
        _full_path = _data.path_info + _url;
    else
        _full_path = _data.path_info + "/" + _url;
}

const std::string &Cgi::getUploadDir(void) { return (_upload_dir); }
void Cgi::setUploadDir(void) {
    if (!_data.path_info.empty()) {
        _upload_dir = _data.path_info.back() == '/' ? _data.path_info + "images/" : _data.path_info + "/images/";
    }
}

const std::string &Cgi::getErrorPath(void) { return (_error_path); }
void Cgi::setErrorPath(void)
{
    _error_path = _data.path_info + _data.error_page;
}

const std::string &Cgi::successUpload(void) const {
    std::string message = R"(
        <div class="alert alert-success mt-3" role="alert">
            File uploaded successfully!
        </div>
    )";
    return (message);
}

const std::string &Cgi::uploadFailed(void) const {
    std::string message = R"(
        <div class="alert alert-danger mt-3" role="alert">
            File upload failed.
        </div>
    )";
    return (message);
}

const std::string &Cgi::fileMissing(void) const {
    std::string message = R"(
        <div class="alert alert-warning mt-3" role="alert">
            No file field found in the form.
        </div>
    )";
    return (message);
}

const std::string &Cgi::successDelete(void) const {
    std::string message = R"(
        <div class="alert alert-success mt-3" role="alert">
            File deleted successfully!
        </div>
    )";
    return (message);
}

const std::string &Cgi::deleteFailed(void) const {
    std::string message = R"(
        <div class="alert alert-danger mt-3" role="alert">
            File delete failed.
        </div>
    )";
    return (message);
}
