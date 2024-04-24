/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_files.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:08:48 by anlima            #+#    #+#             */
/*   Updated: 2024/04/24 14:33:18 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

std::string mime_type(void);
std::string dynamic_content(std::string content_str,
                            std::map<std::string, std::string> params);
void serve_file(int client_socket, std::string const &file_path,
                std::map<std::string, std::string> params);

// mime_type indicates the type of content being served (e.g., text/html for
// HTML files, text/css for CSS files)
std::string mime_type(std::string const &filename) {
    size_t dot_pos = filename.find_last_of('.');

    if (dot_pos != std::string::npos) {
        std::string text = filename.substr(dot_pos);
        if (text == HTML_EXT)
            return (HTML_MIME);
        else if (text == CSS_EXT)
            return (CSS_MIME);
        else if (JS_EXT)
            return (JS_MIME);
    }
    return (DEFAULT_MIME);
}

// std::ios::binary specifies that files should be opened in binary mode. this
// means that files will be read and written as they are, without any
// transformation or interpretation of the data
void serve_file(int client_socket, std::string const &file_path,
                std::map<std::string, std::string> params) {
    std::cout << "Serving file: " << file_path
              << " to client socket: " << client_socket << std::endl;

    std::ifstream file(file_path.c_str(), std::ios::binary);
    // TODO: - handle the error bellow (send 404 not found)
    if (!file.is_open()) {
        std::cout << "error while trying to open the index file" << std::endl;
        return;
    }
    std::stringstream content;
    content << file.rdbuf();
    file.close();
    std::string content_str = dynamic_content(content.str(), params);
    std::stringstream res_headers;
    res_headers << OK_HEADER << CONTENT_TYPE << mime_type(file_path) << "\r\n"
                << CONTENT_LEN << content_str.length() << "\r\n";
    send(client_socket, res_headers.str().c_str(), res_headers.str().length(),
         0);
    send(client_socket, content_str.c_str(), content_str.length(), 0);
}

// in the line content_str.replace(pos - 2, (it->first).length() + 4,
// it->second) the -2 and +4 are taking into account the positions of the
// brackets to be replaced in the line content_str.replace(pos_begin, pos_end -
// pos_begin + 2, "") the +2 takes into account the }} at the end
std::string dynamic_content(std::string content_str,
                            std::map<std::string, std::string> params) {
    if (params.empty()) {
        size_t pos_begin = content_str.find("{{");
        while (pos_begin != std::string::npos) {
            size_t pos_end = content_str.find("}}");
            if (pos_end != std::string::npos)
                content_str.replace(pos_begin, pos_end - pos_begin + 2, "");
            pos_begin = content_str.find("{{");
        }
        return (content_str);
    }
    for (std::map<std::string, std::string>::iterator it = params.begin();
         it != params.end(); ++it) {
        size_t pos = content_str.find(it->first);
        while (pos != std::string::npos) {
            content_str.replace(pos - 2, (it->first).length() + 4, it->second);
            pos = content_str.find(it->first);
        }
    }
    return (content_str);
}
