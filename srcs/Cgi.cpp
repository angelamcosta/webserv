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
{
    setUrl(_data.url, _data.index);
    setFullPath(_data.path_info);
    setUploadDir(_data.path_info);
    setErrorPath(_data.path_info, _data.error_page);
}

Cgi::Cgi(const Cgi &copy)
{
    if (this != &copy) {
        _data = copy.getData();
        _url = copy.getUrl();
        _full_path = copy.getFullPath();
        _upload_dir = copy.getUploadDir();
        _error_path = copy.getErrorPath();
    }
}

Cgi &Cgi::operator=(const Cgi &copy)
{
    if (this != &copy) {
        _data = copy.getData();
        _url = copy.getUrl();
        _full_path = copy.getFullPath();
        _upload_dir = copy.getUploadDir();
        _error_path = copy.getErrorPath();
    }
    return (*this);
}

const s_request &Cgi::getData(void); { return (_data); }
const std::string &Cgi::getUrl(void) { return (_url); }
const std::string &Cgi::getFullPath(void) { return (_full_path); }
const std::string &Cgi::getUploadDir(void) { return (_upload_dir); }
const std::string &Cgi::getErrorPath(void) { return (_error_path); }

void Cgi::setUrl(const std::string url, const std::string index) const
{
    _url = url == "/" ? "/" + index : index;
}

void Cgi::setFullPath(const std::string path_info) const
{
    if (_url[0] == "/" && path_info[-1] == "/")
        _full_path = path_info + _url[1:];
    else if (url.startswith("/") or path_info.endswith("/"))
        _full_path = path_info + _url;
    else:
        _full_path = path_info + "/" + _url;
}

void Cgi::setUploadDir(const std::string path_info) const
{
    _upload_dir = path_info[-1] == "/" ? path_info + "images/" : path_info + "/images/";
}

void Cgi::setErrorPath(const std::string path_info, const std::string error_page) const
{
    _error_path = path_info + error_page;
}

void Cgi::handleRequest(void)
{
    if (_data.method == "invalid_size")
        handleGet("");
    else if (_data.method in _data.allowed_methods)
    {
        else if (_data.method == "GET")
            handleGet("");
        else if (_data.method == "POST")
            message = handlePost(upload_dir, image_data);
            handleGet(message);
        else if (_data.method == "DELETE"):
            message = handleDelete(url, upload_dir, filename)
            handleGet(full_path, dir_listing, error_path,
                       path_info, url, message);
        else
            getFile(path_info + "not_allowed.html", path_info,
                 url, message="", status="405 Not Allowed");
    }
    else
        getFile(path_info + "not_allowed.html", path_info,
                 url, message="", status="405 Not Allowed");
}

void Cgi::handleGet(const std::string message):
    if message == "invalid_size":
        message = upload_failed()
        getFile(full_path, path_info, url, message)
    elif os.path.exists(full_path):
        if os.path.isdir(full_path):
            if dir_listing == "on":
                get_directories(full_path, path_info)
            else:
                getFile(path_info + "forbidden.html", path_info,
                         url, message, "403 Forbidden")
        elif os.path.isfile(full_path):
            if full_path.endswith(('.png', '.jpg', '.jpeg', '.gif')):
                get_image(full_path, path_info, error_path, url)
            else:
                getFile(full_path, path_info, url, message)
    else:
        getFile(error_path, path_info, url, message, "404 Not found")


#include <string>

const std::string &Cgi::success_upload(void) const {
    std::string message = R"(
        <div class="alert alert-success mt-3" role="alert">
            File uploaded successfully!
        </div>
    )";
    return (message);
}

const std::string &Cgi::upload_failed(void) const {
    std::string message = R"(
        <div class="alert alert-danger mt-3" role="alert">
            File upload failed.
        </div>
    )";
    return (message);
}

const std::string &Cgi::file_missing(void) const {
    std::string message = R"(
        <div class="alert alert-warning mt-3" role="alert">
            No file field found in the form.
        </div>
    )";
    return (message);
}

const std::string &Cgi::success_delete(void) const {
    std::string message = R"(
        <div class="alert alert-success mt-3" role="alert">
            File deleted successfully!
        </div>
    )";
    return (message);
}

const std::string &Cgi::delete_failed(void) const {
    std::string message = R"(
        <div class="alert alert-danger mt-3" role="alert">
            File delete failed.
        </div>
    )";
    return (message);
}
