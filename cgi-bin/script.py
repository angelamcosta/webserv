#!/usr/bin/python3

import sys
from methods import handle_get, handle_post, not_allowed

url = sys.argv[1]
request = sys.argv[2]
index = sys.argv[3]
method = sys.argv[4]
PATH_INFO = sys.argv[5]
error_page = sys.argv[6]
dir_listing = sys.argv[7]
allowed_methods = sys.argv[8]
UPLOAD_DIR = PATH_INFO + "images" if PATH_INFO[-1] == "/" else PATH_INFO + "/images"

if (url == "/"):
    url = "/" + index

if (PATH_INFO[-1] == "/" and url[0] == "/"):
    full_path = PATH_INFO + url[1:]
elif (PATH_INFO[-1] == "/" and url[0] != "/") or (PATH_INFO[-1] != "/" and url[0] == "/"):
    full_path = PATH_INFO + url
else:
    full_path = PATH_INFO + "/" + url

error_path = PATH_INFO + error_page

def main():
    if method == "GET" and method in allowed_methods:
        handle_get(full_path, dir_listing, error_path)
    elif method == "POST" and method in allowed_methods:
        handle_post(UPLOAD_DIR, full_path, dir_listing, error_path)
    # elif method == "DELETE" and method in allowed_methods:
    else:
        not_allowed()

if __name__ == "__main__":
    main()