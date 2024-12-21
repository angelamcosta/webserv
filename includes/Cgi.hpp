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
  void setUrl(void);

  const std::string &getFullPath(void);
  void setFullPath(void);

  const std::string &getUploadDir(void);
  void Cgi::setUploadDir(void);

  const std::string &getErrorPath(void);
  void setErrorPath(void);

  const std::string &successUpload(void) const;
  const std::string &uploadFailed(void) const;
  const std::string &fileMissing(void) const;
  const std::string &successDelete(void) const;
  const std::string &deleteFailed(void) const;
};

#endif
