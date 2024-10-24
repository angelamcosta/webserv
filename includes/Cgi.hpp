/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:14:05 by anlima            #+#    #+#             */
/*   Updated: 2024/10/22 16:08:34 by anlima           ###   ########.fr       */
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
  const std::string &getFullPath(void);
  const std::string &getUploadDir(void);
  const std::string &getErrorPath(void);

  void setFullPath(const std::string path_info) const;
  void setUploadDir(const std::string path_info) const;
  void setUrl(const std::string url, const std::string index) const;
  void setErrorPath(const std::string path_info, const std::string error_page) const;

  void handleRequest(void);

  const std::string success_upload(void) const;
  const std::string upload_failed(void) const;
  const std::string file_missing(void) const;
  const std::string success_delete(void) const;
  const std::string delete_failed(void) const;
};

#endif
