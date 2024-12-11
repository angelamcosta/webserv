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

Cgi::Cgi(const s_request &data) : _data(data) {}

Cgi::~Cgi() {}

const std::string &Cgi::getIndex(void) const { return (_data.index); }
const std::string &Cgi::getMethod(void) const { return (_data.method); }
const std::string &Cgi::getPathInfo(void) const { return (_data.path_info); }
const std::string &Cgi::getImageData(void) const { return (_data.image_data); }
const std::string &Cgi::getDirListing(void) const { return (_data.dir_listing); }
const std::string &Cgi::getAllowedMethods(void) const { return (_data.allowed_methods); }

const std::string &Cgi::getUrl(void) const { return (_data.url); }
void  Cgi::setUrl(void) {
    //converter do script
}

const std::string &Cgi::getErrorPage(void) const { return (_data.error_page); }
void  Cgi::setErrorPage(void) {
    // converter do script
}

const std::string &Cgi::getUploadDir(void) const { return _upload_dir; }
void  Cgi::setUploadDir(const std::string upload_dir) {
    // converter do script
}
