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
  Cgi();

public:
  ~Cgi();
  Cgi(const s_request &data);
  Cgi(const Cgi &copy);
  Cgi &operator=(const Cgi &copy);

  const std::string &getIndex(void) const;
  const std::string &getMethod(void) const;
  const std::string &getPathInfo(void) const;
  const std::string &getImageData(void) const;
  const std::string &getDirListing(void) const;
  const std::string &getAllowedMethods(void) const;

  const std::string &getUrl(void) const;
  void  setUrl(void);
  
  const std::string &getErrorPage(void) const;
  void  setErrorPage(void);

  const std::string &getUploadDir(void) const;
  void  setUploadDir(const std::string upload_dir);

  void handleMethods(const std::string &method);
  void handlePost(void);
  void handlePut(void);
  void handleDelete(void);
  const std::string &getFile(const std::string &full_path);

  void sendResponse(void);
};

#endif
