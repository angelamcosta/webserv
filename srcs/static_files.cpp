/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_files.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:08:48 by anlima            #+#    #+#             */
/*   Updated: 2024/04/16 19:25:54 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../webserv.hpp"

std::string mime_type(void);
void serve_file(int client_socket, std::string const &file_path);

// mime_type indicates the type of content being served (e.g., text/html for HTML files, text/css for CSS files)
std::string    mime_type(std::string const &filename)
{
    size_t dot_pos = filename.find_last_of('.');

    if (dot_pos != std::string::npos)
    {
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

// std::ios::binary specifies that files should be opened in binary mode. this means that files will be read and written as they are, without any transformation or interpretation of the data
void serve_file(int client_socket, std::string const &file_path)
{
    std::cout << "Serving file: " << file_path << " to client socket: " << client_socket << std::endl;
    
    std::ifstream file(file_path.c_str(), std::ios::binary);
    // TODO: - handle the error bellow (send 404 not found)
    if (!file.is_open())
    {
        std::cout << "error while trying to open the index file" << std::endl;
        return ;
    }
    std::stringstream content;
    content << file.rdbuf();
    file.close();
    
    std::stringstream res_headers;
    res_headers << OK_HEADER << CONTENT_TYPE << mime_type(file_path) << "\r\n" << CONTENT_LEN << content.str().length() << "\r\n";
    send(client_socket, res_headers.str().c_str(), res_headers.str().length(), 0);
    send(client_socket, content.str().c_str(), content.str().length(), 0);
}
