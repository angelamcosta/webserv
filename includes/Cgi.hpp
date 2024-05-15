/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:14:05 by anlima            #+#    #+#             */
/*   Updated: 2024/05/14 16:58:46 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include "macros.hpp"

class Cgi {
  private:
    std::string _url;
    std::string _body;
    std::string _method;
    std::string _request;
    std::string _filename;
    std::string _file_path;
    std::string _mime_type;
    std::string _error_page;
    Cgi();

  public:
    ~Cgi();
    Cgi(std::string url, std::string body, std::string method,
        std::string request, std::string filename, std::string file_path,
        std::string error_page);
    Cgi(const Cgi &copy);
    Cgi &operator=(const Cgi &copy);

    const std::string &getUrl(void) const;
    const std::string &getBody(void) const;
    const std::string &getMethod(void) const;
    const std::string &getFilename(void) const;
    const std::string &getFilePath(void) const;
    const std::string &getErrorPage(void) const;

    void handleMethods(const std::string &method);
    void handlePost(void);
    void handlePut(void);
    void handleDelete(void);

    void sendResponse(void);
};

#endif
