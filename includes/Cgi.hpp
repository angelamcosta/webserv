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
  std::string _upload_dir;
  std::string _url;
  std::string _full_path;
  std::string _error_path;
  Cgi();

public:
  ~Cgi();
  Cgi(const s_request &data, const std::string &upload_dir, const std::string &url, const std::string &full_path, const std::string &error_path);
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
  const std::string &getFile(const std::string &full_path);

  void sendResponse(void);
};

#endif
