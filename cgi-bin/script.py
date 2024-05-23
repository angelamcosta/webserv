#!/usr/bin/python3

import sys
import cgi
from methods import handle_get, handle_post, not_allowed

url = sys.argv[1]
request = sys.argv[2]
index = sys.argv[3]
method = sys.argv[4]
PATH_INFO = sys.argv[5]
error_page = sys.argv[6]
dir_listing = sys.argv[7]
allowed_methods = sys.argv[8]
UPLOAD_DIR = PATH_INFO + "images/" if PATH_INFO[-1] == "/" else PATH_INFO + "/images/"

if (url == "/"):
    url = "/" + index
if ".py" in url:
    full_path = PATH_INFO + index if PATH_INFO[-1] == "/" else PATH_INFO + "/" + index
elif (PATH_INFO[-1] == "/" and url[0] == "/"):
    full_path = PATH_INFO + url[1:]
elif (PATH_INFO[-1] == "/" and url[0] != "/") or (PATH_INFO[-1] != "/" and url[0] == "/"):
    full_path = PATH_INFO + url
else:
    full_path = PATH_INFO + "/" + url
error_path = PATH_INFO + error_page

def print_variables(url, request, index, method, PATH_INFO, error_page, dir_listing, allowed_methods, UPLOAD_DIR):
    print("Content-type: text/html\r\n\r\n")

    form = cgi.FieldStorage()

    print("<html><body>")
    print("<h1>Form Data:</h1>")
    print("<ul>")
    for field in form.keys():
        print(f"<li>{field}: {form[field].value}</li>")
    print("</ul>")
    print("</body></html>")
    print("URL:", url)
    print("Request:", request)
    print("Index:", index)
    print("Method:", method)
    print("full_path:", PATH_INFO)
    print("Error Page:", error_page)
    print("Directory Listing:", dir_listing)
    print("Allowed Methods:", allowed_methods)
    print("UPLOAD_DIR:", UPLOAD_DIR)
    print("\n----------\nEnd of print\n")

def main():
    if not url:
        return
    # print_variables(url, request, index, method, full_path, error_page, dir_listing, allowed_methods, UPLOAD_DIR)
    if method == "GET" and method in allowed_methods:
        handle_get(full_path, dir_listing, error_path)
    elif method == "POST" and method in allowed_methods:
        handle_post(UPLOAD_DIR, full_path, dir_listing, error_path)
    # elif method == "DELETE" and method in allowed_methods:
    else:
        not_allowed()

if __name__ == "__main__":
    main()