#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "macros.hpp"

class Request {
  private:
    std::string _url;
    std::string _method;
    std::string _request;
    std::string _filename;

  public:
    Request();
    ~Request();
    Request(const Request& copy);
    Request &operator=(const Request &copy);
    
    Request(const std::string &request);

    const std::string &getUrl() const;
    void setUrl(const std::string &url);

    const std::string &getMethod() const;
    void setMethod(const std::string &method);

    const std::string &getRequest() const;
    void setRequest(const std::string &request);

    const std::string &getFilename() const;
    void setFilename(const std::string &filename);

    void processRequest(const std::string &request);
};

#endif