#!/usr/bin/python3

import sys
from methods import handle_get, handle_post, handle_delete, get_file
from utils import get_upload_dir, get_full_path


def main():
    data = sys.stdin.read()
    args = data.splitlines()
    url = args[0]
    index = args[1]
    method = args[2]
    path_info = args[3] if args[3][-1] == "/" else args[3] + "/"
    error_page = args[4] if args[4][-1] == "/" else args[4] + "/"
    dir_listing = args[5]
    allowed_methods = args[6]
    image_data = args[7]
    filename = args[8]
    upload_dir = get_upload_dir(path_info)
    url = "/" + index if url == "/" else url
    full_path = get_full_path(url, path_info)
    error_path = path_info + error_page if path_info[-1] != "/" else path_info[:-1] + error_page
    if method == "invalid_size":
        handle_get(full_path, dir_listing,
                    error_path, path_info, url, method)
    elif method in allowed_methods:
        if method == "GET":
            if "_method=DELETE" in url:
                filename = url[url.find("_filename=") + 10:]
                url = url[:url.find("?")]
                full_path = full_path[:full_path.find("?")]
                message = handle_delete(url, upload_dir, filename)
                handle_get(full_path, dir_listing, error_path,
                       path_info, url, message)
            else:
                handle_get(full_path, dir_listing, error_path, path_info, url)
        elif method == "POST":
            message = handle_post(upload_dir, image_data)
            handle_get(full_path, dir_listing, error_path,
                       path_info, url, message)
        else:
            get_file(path_info + "not_allowed.html", path_info,
                 url, message="", status="405 Not Allowed")
    else:
        get_file(path_info + "not_allowed.html", path_info,
                 url, message="", status="405 Not Allowed")


if __name__ == "__main__":
    main()
