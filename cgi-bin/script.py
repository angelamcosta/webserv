#!/usr/bin/python3

import sys
import os

url = sys.argv[1] if sys.argv[1] != "/" else "/index.html"
body = sys.argv[2]
method = sys.argv[3]
request = sys.argv[4]
filename = sys.argv[5]
error_page = sys.argv[6]
# allowed_methods = sys.argv[7]
PATH_INFO = "./public"

def generate_response(status, file):
    print (f"HTTP/1.1 {status} \r\nContent-Length: {len(file)}\r\n\r\n{file}")
    
def print_error():
    try:
        with open(error_page, "r") as f:
            generate_response("404 Not found", f.read())
    except OSError:
        generate_response("404 Not found", "<h1>ERROR: Could not find the specified file</h1>")

if (os.path.isfile(PATH_INFO + url)):
    try:
        with open(PATH_INFO + url, "r") as f:
            generate_response("200 OK", f.read())
    except OSError:
        print_error()
else:
    print_error()

# implement methods