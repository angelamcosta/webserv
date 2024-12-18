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
const std::string &Cgi::getFullPath(void) { return (_full_path); }
const std::string &Cgi::getUploadDir(void) { return (_upload_dir); }
const std::string &Cgi::getErrorPath(void) { return (_error_path); }

// void Cgi::setUrl(void) const
// {
//     _url = _data.url == "/" ? "/" + _data.index : _data.index;
// }

// void Cgi::setFullPath(const std::string path_info) const
// {
//     if (_url[0] == "/" && path_info[-1] == "/")
//         _full_path = path_info + _url[1:];
//     else if (url.startswith("/") or path_info.endswith("/"))
//         _full_path = path_info + _url;
//     else:
//         _full_path = path_info + "/" + _url;
// }

// void Cgi::setUploadDir(const std::string path_info) const
// {
//     _upload_dir = path_info.back == '/' ? path_info + "images/" : path_info + "/images/";
// }

// void Cgi::setErrorPath(const std::string path_info, const std::string error_page) const
// {
//     _error_path = path_info + error_page;
// }

// void Cgi::handleRequest(void)
// {
//     if (_data.method == "invalid_size")
//         handleGet("");
//     else if (_data.method in _data.allowed_methods)
//     {
//         else if (_data.method == "GET")
//             handleGet("");
//         else if (_data.method == "POST")
//             message = handlePost(upload_dir, image_data);
//             handleGet(message);
//         else if (_data.method == "DELETE"):
//             message = handleDelete(url, upload_dir, filename)
//             handleGet(full_path, dir_listing, error_path,
//                        path_info, url, message);
//         else
//             getFile(path_info + "not_allowed.html", path_info,
//                  url, message="", status="405 Not Allowed");
//     }
//     else
//         getFile(path_info + "not_allowed.html", path_info,
//                  url, message="", status="405 Not Allowed");
// }

// void Cgi::handleGet(const std::string message):
//     if message == "invalid_size":
//         message = upload_failed()
//         getFile(full_path, path_info, url, message)
//     elif os.path.exists(full_path):
//         if os.path.isdir(full_path):
//             if dir_listing == "on":
//                 get_directories(full_path, path_info)
//             else:
//                 getFile(path_info + "forbidden.html", path_info,
//                          url, message, "403 Forbidden")
//         elif os.path.isfile(full_path):
//             if full_path.endswith(('.png', '.jpg', '.jpeg', '.gif')):
//                 get_image(full_path, path_info, error_path, url)
//             else:
//                 getFile(full_path, path_info, url, message)
//     else:
//         getFile(error_path, path_info, url, message, "404 Not found");

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
