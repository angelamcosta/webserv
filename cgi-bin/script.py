#!/usr/bin/python3

import sys
from methods import handle_get, handle_post, not_allowed
from utils import get_upload_dir, get_full_path


def main():
    data = sys.stdin.read()
    args = data.splitlines()
    url = args[0]
    index = args[1]
    method = args[2]
    path_info = args[3]
    error_page = args[4]
    dir_listing = args[5]
    allowed_methods = args[6]
    image_data = args[7]
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
