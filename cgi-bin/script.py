#!/usr/bin/python3

import os
import sys
from methods import handle_get, handle_post, not_allowed
from utils import get_upload_dir, get_full_path

def main():
    url = sys.argv[1]
    index = sys.argv[2]
    method = sys.argv[3]
    path_info = sys.argv[4]
    error_page = sys.argv[5]
    dir_listing = sys.argv[6]
    allowed_methods = sys.argv[7]
    image_data = sys.argv[8]
    upload_dir = get_upload_dir(path_info)
    url = "/" + index if url == "/" else url
    full_path = get_full_path(url, path_info, index)
    error_path = path_info + error_page

    if method == "GET":
        handle_get(full_path, dir_listing, error_path, path_info)
    elif method == "POST" and method in allowed_methods:
        message = handle_post(upload_dir, image_data)
        handle_get(full_path, dir_listing, error_path, path_info, message)
    # elif method == "DELETE" and method in allowed_methods:
    else:
        not_allowed(path_info, full_path)

if __name__ == "__main__":
    main()