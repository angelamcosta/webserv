# <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Objects/Computer%20Disk.png" alt="Computer Disk" width="25" height="25" /> webserv

<div align=center>
  
  ![badge](https://raw.githubusercontent.com/angelamcosta/angelamcosta/main/42_badges/webservn.png)

  <table>
  <tr>
    <td align="center"><a href="https://github.com/angelamcosta"><img src="https://avatars.githubusercontent.com/u/14792447?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Angela Lima</b></sub></a><br /><a href="https://github.com/angelamcosta" title="Angela Lima"></a></td>
    <td align="center"><a href="https://github.com/gcssilva"><img src="https://avatars.githubusercontent.com/u/108615291?v=4" width="100px;" alt=""/><br /><sub><b>Gustavo Silva</b></sub></a><br /><a href="https://github.com/gcssilva" title="Gustavo Silva"></a></td>
    <td align="center"><a href="http://github.com/mgdiogo"><img src="https://avatars.githubusercontent.com/u/109535612?v=4?s=100" width="100px;" alt=""/><br /><sub><b>Miguel Diogo</b></sub></a><br /><a href="https://github.com/mgdiogo/" title="Miguel Diogo"></a></td>
  </tr>
</table>

<img alt="GitHub Language Count" src="https://img.shields.io/github/languages/count/angelamcosta/webserv" /> <img alt="GitHub Top Language" src="https://img.shields.io/github/languages/top/angelamcosta/webserv" /> <img alt="GitHub Contributors" src="https://img.shields.io/github/contributors/angelamcosta/webserv" /> <img alt="GitHub Last Commit" src="https://img.shields.io/github/last-commit/angelamcosta/webserv" /> <a href="https://wakatime.com/badge/user/0c29d5b3-c30b-4e1a-ad07-2da3bd4f7e05/project/018e8011-e2e3-4db8-b722-5fdd0683bfaf"><img src="https://wakatime.com/badge/user/0c29d5b3-c30b-4e1a-ad07-2da3bd4f7e05/project/018e8011-e2e3-4db8-b722-5fdd0683bfaf.svg" alt="wakatime"></a>

</div>

Webserv is a C++ 98 HTTP server. The subject of the project can be found [here](https://raw.githubusercontent.com/angelamcosta/webserv/main/en.subject.pdf).

## 📜 Mandatory Features

- The program must never crash or quit unexpectedly.
- A Makefile must be provided, adhering to specific rules.
- Code compilation must utilize c++ with the flags -Wall -Wextra -Werror.
- Compliance with C++ 98 standard is mandatory.
- Usage of external libraries, including Boost, is prohibited.

## 🚀 Mandatory Part 

### Requirements
- Configuration file handling: The program must accept a configuration file as an argument or use a default path.
- Non-blocking behavior: The server should never block, and clients can be gracefully handled if necessary.
- Use of only one poll() (or equivalent) for all I/O operations.
- Accurate HTTP response status codes.
- Ability to serve static websites and handle file uploads.
- Support for GET, POST, and DELETE methods.
- Stress testing to ensure the server remains available.
- Compatibility with a chosen web browser.
- Default error pages.
- Ability to listen to multiple ports.

### Configuration File
- Inspiration from NGINX configuration file structure.
- Configuration options for server port, host, server names, default error pages, and more.
- Setup of routes with various configuration options, including HTTP methods, redirection, directory listings, CGI execution, and handling of uploaded files.

## 🚀 Getting Started 
To get started with **webserv**, follow these steps:

1. Clone the repository: `git clone https://github.com/your/repo.git`
2. Navigate to the project directory: `cd webserv`
3. Compile the source files using the provided Makefile: `make`
4. Run the executable with a configuration file: `./webserv [configuration_file]`

## 📚 Glossary

- [Base64 Encode Algorithm](https://base64.guru/learn/base64-algorithm/encode)
- [I/O Multiplexing: The select and poll Functions](https://notes.shichao.io/unp/ch6/)