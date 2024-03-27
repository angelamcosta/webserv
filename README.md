# <img src="https://raw.githubusercontent.com/Tarikul-Islam-Anik/Animated-Fluent-Emojis/master/Emojis/Objects/Computer%20Disk.png" alt="Computer Disk" width="25" height="25" /> webserv

<div align=center>
  
  ![badge](https://raw.githubusercontent.com/angelamcosta/angelamcosta/main/42_badges/webservn.png)
</div>

Webserv is about writing a C++ 98 HTTP server. The subject of the project can be found [here](https://raw.githubusercontent.com/angelamcosta/webserv/main/en.subject.pdf).

## 📜 Mandatory Features
Before delving into the specifics of the **webserv** project, it's crucial to understand and adhere to the general rules outlined below:

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
