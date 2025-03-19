/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:31:13 by anlima            #+#    #+#             */
/*   Updated: 2025/02/06 15:53:08 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Utils.hpp"
#include "../includes/Requests.hpp"

Utils::~Utils() {}

Utils::Utils(const s_request &data) : _data(data), _url(data.url), _index(data.index), _method(data.method), _filename(data.filename), _template(""), _full_path(""), _path_info(data.path_info), _image_data(data.image_data), _error_page(data.error_page), _error_path(""), _upload_dir(""), _dir_listing(data.dir_listing), _allowed_methods(data.allowed_methods)
{
    setUrl();
    setTemplate();
    setFullPath();
    setUploadDir();
    setErrorPath();
}

Utils::Utils(const Utils &copy)
{
    if (this != &copy)
    {
        _data = copy._data;
        _url = copy._url;
        _index = copy._index;
        _method = copy._method;
        _filename = copy._filename;
        _template = copy._template;
        _full_path = copy._full_path;
        _path_info = copy._path_info;
        _image_data = copy._image_data;
        _error_page = copy._error_page;
        _error_path = copy._error_path;
        _upload_dir = copy._upload_dir;
        _dir_listing = copy._dir_listing;
        _allowed_methods = copy._allowed_methods;
    }
}

Utils &Utils::operator=(const Utils &copy)
{
    if (this != &copy)
    {
        _data = copy._data;
        _url = copy._url;
        _index = copy._index;
        _method = copy._method;
        _filename = copy._filename;
        _template = copy._template;
        _full_path = copy._full_path;
        _path_info = copy._path_info;
        _image_data = copy._image_data;
        _error_page = copy._error_page;
        _error_path = copy._error_path;
        _upload_dir = copy._upload_dir;
        _dir_listing = copy._dir_listing;
        _allowed_methods = copy._allowed_methods;
    }
    return (*this);
}

const s_request &Utils::getData(void) { return (_data); }

const std::string &Utils::getUrl(void) { return (_url); }
void Utils::setUrl(void)
{
    if (_data.url == "" || _data.url == "/")
        _url = "/index.html";
    else
        _url = _data.url;
}

std::string &Utils::getTemplate(void) { return (_template); }
void Utils::setTemplate(void)
{
    _template = _path_info + "template.html";
}

std::string &Utils::getFullPath(void) { return (_full_path); }
void Utils::setFullPath(void)
{
    if (!_url.empty() && _url[0] == '/' && !_data.path_info.empty() && _data.path_info[_data.path_info.length() - 1] == '/')
        _full_path = _data.path_info + _url.substr(1);
    else if ((!_url.empty() && _url[0] == '/') || (!_data.path_info.empty() && _data.path_info[_data.path_info.length() - 1] == '/'))
        _full_path = _data.path_info + _url;
    else
        _full_path = _data.path_info + "/" + _url;
}

std::string &Utils::getUploadDir(void) { return (_upload_dir); }
void Utils::setUploadDir(void)
{
    if (!_data.path_info.empty())
        _upload_dir = _data.path_info[_data.path_info.length() - 1] == '/' ? _data.path_info + "images/" : _data.path_info + "/images/";
}

std::string &Utils::getErrorPath(void) { return (_error_path); }
void Utils::setErrorPath(void)
{
    _error_path = _path_info + _error_page.substr(1);
}

const std::string Utils::successUpload(void) const
{
    return ("<div class=\"alert alert-success mt-3\" role=\"alert\">\n"
            "    File uploaded successfully!\n"
            "</div>\n");
}

const std::string Utils::uploadFailed(void) const
{
    return ("<div class=\"alert alert-danger mt-3\" role=\"alert\">\n"
            "    File upload failed.\n"
            "</div>\n");
}

const std::string Utils::fileMissing(void) const
{
    return ("<div class=\"alert alert-warning mt-3\" role=\"alert\">\n"
            "    File not found.\n"
            "</div>\n");
}

const std::string Utils::successDelete(void) const
{
    return ("<div class=\"alert alert-success mt-3\" role=\"alert\">\n"
            "    File deleted successfully!\n"
            "</div>\n");
}

const std::string Utils::deleteFailed(void) const
{
    return ("<div class=\"alert alert-danger mt-3\" role=\"alert\">\n"
            "    File delete failed.\n"
            "</div>\n");
}

const std::string Utils::emptyFolder(void) const
{
    return ("<div class=\"alert alert-secondary mt-3\" role=\"alert\">\n"
            "    The pond is empty right now.\n"
            "</div>\n");
}

const std::string Utils::generateCards(std::string path_info, std::string url) const
{
    std::ostringstream cards;
    std::vector<std::string> images;

    if (isDirectory(_path_info))
    {
        DIR *dir = opendir(path_info.c_str());
        if (dir)
        {
            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL)
            {
                std::string filename(entry->d_name);
                if (filename != "." && filename != "..")
                    images.push_back(filename);
            }
            closedir(dir);
        }
    }
    if (images.empty())
    {
        return "<div class=\"alert alert-secondary\" role=\"alert\">\n"
               "    The pond is empty right now.\n"
               "</div>\n";
    }
    for (std::vector<std::string>::const_iterator it = images.begin(); it != images.end(); ++it)
    {
        std::string path = "../images/" + *it;
        cards << "            <div class=\"col\">\n"
              << "                <div class=\"card shadow-sm\">\n"
              << "                    <img src=\"" << path << "\" class=\"card-img-top\" width=\"100%\" height=\"225\" style=\"object-fit: cover;\">\n"
              << "                    <div class=\"card-body\">\n"
              << "                        <div class=\"d-flex justify-content-between align-items-center\">\n"
              << "                            <div class=\"d-grid gap-2 d-md-flex justify-content-md-end\">\n"
              << "                                <a class=\"btn btn-outline-primary\" href=\"" << path << "\" role=\"button\">View</a>\n"
              << "                                <form method=\"DELETE\" action=\"" << url << "\">\n"
              << "                                    <input type=\"hidden\" name=\"_method\" value=\"DELETE\">\n"
              << "                                    <input type=\"hidden\" name=\"_filename\" value=\"" << *it << "\">\n"
              << "                                    <button type=\"submit\" class=\"btn btn-outline-secondary\" role=\"button\">Delete</button>\n"
              << "                                </form>\n"
              << "                            </div>\n"
              << "                        </div>\n"
              << "                    </div>\n"
              << "                </div>\n"
              << "            </div>\n";
    }

    return (cards.str());
}

bool Utils::pathExists(const std::string &path) const
{
    struct stat s;
    return (stat(path.c_str(), &s) == 0 && s.st_mode & S_IFREG);
}

bool Utils::isDirectory(const std::string &path) const
{
    struct stat s;
    return (stat(path.c_str(), &s) == 0 && s.st_mode & S_IFDIR);
}

void Utils::handleMethod(std::string message)
{
    if (message == "invalid_size")
    {
        message = uploadFailed();
        getFile(_full_path, _data.path_info, _url, message, "403 Forbidden");
    }
    else if (_allowed_methods.find(_method) != std::string::npos)
    {
        if (_url.find("_method=DELETE") != std::string::npos)
        {
            message = handlePost();
            if (message == "not allowed")
                getFile(_full_path, _data.path_info + "not_allowed.html", _url, message, "405 Not Allowed");
            else
                handleGet(message);
        }
        else if (_method == "GET")
            handleGet(message);
        else if ((_method == "POST") && (_allowed_methods.find("POST") != std::string::npos))
        {
            message = handlePost();
            handleGet(message);
        }
    }
    else
        getFile(_error_path, _data.path_info, _url, message, "405 Not Allowed");
}

std::string Utils::generateUuid(void)
{
    std::ostringstream uuid;
    std::srand(std::time(0));

    for (int i = 0; i < 8; ++i)
        uuid << std::hex << (std::rand() % 16);
    uuid << "-";
    for (int i = 0; i < 4; ++i)
        uuid << std::hex << (std::rand() % 16);
    uuid << "-";
    for (int i = 0; i < 4; ++i)
        uuid << std::hex << (std::rand() % 16);
    uuid << "-";
    for (int i = 0; i < 4; ++i)
        uuid << std::hex << (std::rand() % 16);
    uuid << "-";
    for (int i = 0; i < 12; ++i)
        uuid << std::hex << (std::rand() % 16);
    return uuid.str();
}

void Utils::handleGet(std::string &message)
{
    if (!isDirectory(_full_path) && !pathExists(_full_path))
    {
        getFile(_error_path, _data.path_info, _url, message, "404 Not Found");
        return;
    }
    else
    {
        if (isDirectory(_full_path))
        {
            if (_data.dir_listing == "on")
                getDirectories(_full_path, _data.path_info);
            else
                getFile(_full_path, _data.path_info + "forbidden.html", _url, message, "403 Forbidden");
        }
        else if (pathExists(_full_path))
        {
            // printVariables();
            if (isImage())
                getImage(_full_path, _data.path_info, _error_path, _url, message, "200 OK");
            else
                getFile(_full_path, _data.path_info, _url, message, "200 OK");
        }
    }
}

std::string Utils::handleDelete(void)
{
    if ((_url.find("_method=DELETE") != std::string::npos) && (_allowed_methods.find("DELETE") != std::string::npos))
    {
        int index = _url.find("_filename=");
        _filename = _url.substr(index + 10);
        std::remove((_data.path_info + "/images/" + _filename).c_str());
        if (pathExists(_full_path))
            return deleteFailed();
        else
            return successDelete();
    }
    return "not allowed";
}

std::string Utils::handlePost(void)
{
    if (_url.find("_method=DELETE") != std::string::npos)
        return handleDelete();
    else
    {
        std::string valid_extensions[] = {".png", ".jpg", ".jpeg", ".gif"};
        if (_image_data == "")
            return fileMissing();
        else
        {
            size_t index = _filename.find_last_of(".");
            if (index == std::string::npos)
                return uploadFailed();
            else
            {
                std::string file_extension = _filename.substr(index);
                if (valid_extensions->find(file_extension) == std::string::npos)
                    return uploadFailed();
                std::string binary_data = base64_decode(_image_data);
                std::string filename = _upload_dir + generateUuid() + file_extension;
                std::ofstream outfile(filename.c_str(), std::ofstream::binary);
                if (!outfile)
                    return uploadFailed();

                outfile.write(binary_data.c_str(), binary_data.size());
                outfile.close();
            }
        }
    }
    return successUpload();
}

void Utils::getFile(const std::string &full_path, const std::string &path_info, const std::string &url,
                    const std::string &message = "", const std::string &status = "200 OK")
{
    std::string new_file;

    if (isDirectory(full_path.c_str()))
        new_file = path_info;
    else
        new_file = full_path;
    std::ifstream file(new_file.c_str());
    if (!file.is_open())
    {
        generateResponse("404 Not Found",
                         "<h1>ERROR: Could not find the specified file</h1>",
                         full_path, loadTemplateFile());
        return;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();
    file.close();

    size_t pos;
    while ((pos = text.find("{{alert}}")) != std::string::npos)
        text.replace(pos, 9, message);

    if ((pos = text.find("{{images}}")) != std::string::npos)
    {
        std::string cards = generateCards(path_info + "images", url);
        text.replace(pos, 10, cards);
    }
    generateResponse(status, text, full_path, loadTemplateFile());
}

std::string Utils::loadTemplateFile(void)
{
    std::string template_path = getTemplate();
    std::ifstream file(template_path.c_str());

    if (!file.is_open())
        return "";
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return (buffer.str());
}

std::string Utils::generateHeaders(const std::string &status, size_t content_length, const std::string &filename, std::string content_type = "text/html")
{
    std::ostringstream headers;
    headers << "HTTP/1.1 " << status << "\r\n"
            << "Content-Length: " << content_length << "\r\n"
            << "Content-Disposition: inline; filename=\"" << filename << "\"\r\n"
            << "Content-Type: " << content_type << "\r\n"
            << "\r\n";
    return (headers.str());
}

void Utils::generateResponse(const std::string &status, const std::string &content, const std::string &full_path, const std::string &template_str)
{
    std::string updated_template = template_str;
    std::string placeholder = "{{placeholder}}";
    size_t pos = updated_template.find(placeholder);
    if (pos != std::string::npos)
        updated_template.replace(pos, placeholder.length(), content);
    size_t slashPos = full_path.find_last_of("/\\");
    std::string filename = (slashPos != std::string::npos) ? full_path.substr(slashPos + 1) : full_path;
    size_t contentLength = updated_template.size();
    std::string headers = generateHeaders(status, contentLength, filename);
    std::cout << headers << updated_template << std::endl;
}

void Utils::getDirectories(const std::string &full_path, const std::string &path_info)
{
    std::vector<std::string> files;
    if (isDirectory(full_path))
    {
        DIR *dir = opendir(full_path.c_str());
        if (dir != NULL)
        {
            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL)
            {
                std::string name = entry->d_name;
                if (name != "." && name != "..")
                    files.push_back(name);
            }
            closedir(dir);
        }
    }
    else
    {
        getFile(_error_path, _data.path_info, _url, "", "404 Not Found");
        return;
    }

    std::string template_file = loadTemplateFile();
    std::string file_list_HTML = generateHTMLList(files);
    std::string html_code =
        "<div class=\"container\">"
        "<div class=\"row\">"
        "<div class=\"col-md-12\">"
        "<div class=\"error-template\">"
        "<h1>" +
        full_path + "</h1>"
                    "<div class=\"error-details\">" +
        file_list_HTML +
        "</div>"
        "</div>"
        "</div>"
        "</div>"
        "</div>";

    generateResponse("200 OK", html_code, path_info + "index.html", template_file);
}

std::string Utils::generateHTMLList(const std::vector<std::string> &files)
{
    std::ostringstream html_stream;
    html_stream << "<ul>";
    for (size_t i = 0; i < files.size(); ++i)
        html_stream << "<li>" << files[i] << "</li>";
    html_stream << "</ul>";
    return (html_stream.str());
}

void Utils::getImage(const std::string full_path, const std::string path_info, const std::string error_path, const std::string url, const std::string message, const std::string status)
{
    std::ifstream file(full_path.c_str(), std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        getFile(error_path, path_info, url, message, "404 Not Found");
        return;
    }

    std::string mime_type;
    size_t dot_pos = full_path.find_last_of(".");
    if (dot_pos != std::string::npos)
    {
        std::string extension = full_path.substr(dot_pos);
        if (extension == ".png")
            mime_type = "image/png";
        else if (extension == ".jpg" || extension == ".jpeg")
            mime_type = "image/jpeg";
        else if (extension == ".gif")
            mime_type = "image/gif";
        else
        {
            getFile(error_path, path_info, url, message, "415 Unsupported Media Type");
            return;
        }
    }
    else
    {
        getFile(error_path, path_info, url, message, "415 Unsupported Media Type");
        return;
    }

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    if (size <= 0)
    {
        getFile(error_path, path_info, url, message, "404 Not Found");
        return;
    }

    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size))
    {
        getFile(error_path, path_info, url, message, "500 Internal Server Error");
        return;
    }

    std::string headers = generateHeaders(status, size, _full_path.substr(_full_path.find_last_of("/") + 1), mime_type);
    std::cout << headers;
    std::cout.write(buffer.data(), size);
}

std::string Utils::base64_decode(const std::string &encoded)
{
    const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    if (encoded.length() % 4 != 0)
        throw std::runtime_error("Invalid Base64 encoded string length");

    std::vector<unsigned char> decoded_data;
    int i = 0;
    unsigned char char_array_4[4], char_array_3[3];

    for (size_t idx = 0; idx < encoded.length(); idx++)
    {
        char current_char = encoded[idx];
        if (current_char == '=')
            break;

        size_t char_pos = base64_chars.find(current_char);
        if (char_pos == std::string::npos)
            continue;

        char_array_4[i++] = static_cast<unsigned char>(char_pos);
        if (i == 4)
        {
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (int k = 0; k < 3; k++)
            {
                decoded_data.push_back(char_array_3[k]);
            }
            i = 0;
        }
    }

    if (i > 0)
    {
        for (int k = i; k < 4; k++)
            char_array_4[k] = 0;

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (int k = 0; k < i - 1; k++)
            decoded_data.push_back(char_array_3[k]);
    }

    return std::string(decoded_data.begin(), decoded_data.end());
}

bool Utils::isImage(void)
{
    if (_full_path.substr(_full_path.size() - 4) == ".png" ||
        _full_path.substr(_full_path.size() - 4) == ".jpg" ||
        _full_path.substr(_full_path.size() - 5) == ".jpeg" ||
        _full_path.substr(_full_path.size() - 4) == ".gif")
        return true;
    return false;
}

void Utils::printVariables(void)
{
    std::cout << "_url: " << _url << "\n";
    std::cout << "_index: " << _index << "\n";
    std::cout << "_method: " << _method << "\n";
    std::cout << "_filename: " << _filename << "\n";
    std::cout << "_template: " << _template << "\n";
    std::cout << "_full_path: " << _full_path << "\n";
    std::cout << "_path_info: " << _path_info << "\n";
    std::cout << "_image_data: " << _image_data << "\n";
    std::cout << "_error_page: " << _error_page << "\n";
    std::cout << "_error_path: " << _error_path << "\n";
    std::cout << "_upload_dir: " << _upload_dir << "\n";
    std::cout << "_dir_listing: " << _dir_listing << "\n";
    std::cout << "_allowed_methods: " << _allowed_methods << "\n";
    // std::cout << "_get_template: " << getTemplate() << std::endl;
}
