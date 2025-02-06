/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:14:05 by anlima            #+#    #+#             */
/*   Updated: 2025/02/06 13:51:48 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include "macros.hpp"

class Cgi
{
private:
    s_request _data;
    std::string _url;
    std::string _template;
    std::string _full_path;
    std::string _upload_dir;
    std::string _error_path;

    Cgi();

public:
    ~Cgi();
    Cgi(const s_request &data);
    Cgi(const Cgi &copy);
    Cgi &operator=(const Cgi &copy);

    const s_request &getData(void);

    const std::string &getUrl(void);
    void setUrl(void);

    std::string &getTemplate(void);
    void setTemplate(void);

    std::string &getFullPath(void);
    void setFullPath(void);

    std::string &getUploadDir(void);
    void setUploadDir(void);

    std::string &getErrorPath(void);
    void setErrorPath(void);

    const std::string emptyFolder(void) const;
    const std::string fileMissing(void) const;
    const std::string deleteFailed(void) const;
    const std::string uploadFailed(void) const;
    const std::string successUpload(void) const;
    const std::string successDelete(void) const;
    const std::string generateCards(std::string path_info, std::string url) const;

    void handleMethod(std::string message);
    void getFile(const std::string &full_path, const std::string &path_info, const std::string &url, const std::string &message, const std::string &status);
    void generateResponse(const std::string &status, const std::string &content, const std::string &full_path, const std::string &template_str);
    std::string loadTemplateFile(const std::string &path_info);
    std::string generateHeaders(const std::string &status, size_t content_length, const std::string &filename);
    void getDirectories(const std::string &full_path, const std::string &path_info);
    void getImage(const std::string full_path, const std::string path_info, const std::string error_path, const std::string url, const std::string message, const std::string status);
    std::string generateHTMLList(const std::vector<std::string> &files);
};

#endif
