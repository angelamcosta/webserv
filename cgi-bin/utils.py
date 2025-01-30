#!/usr/bin/python3

import os
import datetime
import mimetypes


def generate_response(status, content, full_path, template=""):
    template = template.replace("{{placeholder}}", content)
    filename = os.path.basename(full_path)
    content_length = len(template)
    headers = generate_headers(status, content_length, filename)
    print(headers + '\r\n' + template)


def generate_headers(status, content_length, filename):
    headers = f"HTTP/1.1 {status}\r\n"
    current_date = datetime.datetime.utcnow().strftime('%a, %d %b %Y %H:%M:%S GMT')
    headers += f"Date: {current_date}\r\n"
    headers += f"Content-Length: {content_length}\r\n"
    content_type, _ = mimetypes.guess_type(filename)
    if content_type is None:
        content_type = 'application/octet-stream'
    headers += f"Content-Type: {content_type}\r\n"
    headers += "Connection: close\r\n"
    return headers


def get_upload_dir(path_info):
    upload_dir = path_info + \
        "images/" if path_info[-1] == "/" else path_info + "/images/"
    return upload_dir


def get_full_path(url, path_info, index):
    if url.startswith("/") and path_info.endswith("/"):
        full_path = path_info + url[1:]
    elif url.startswith("/") or path_info.endswith("/"):
        full_path = path_info + url
    else:
        full_path = path_info + "/" + url
    return full_path


def load_template_file(path_info):
    path_info = path_info + \
        "template.html" if path_info[-1] == "/" else path_info + \
        "/template.html"
    with open(path_info, 'r') as f:
        template = f.read()
    return (template)


def generate_cards(directory, url):
    images = os.listdir(directory)
    cards = ''
    if not images:
        res = """<div class="alert alert-secondary" role="alert">
                    The pond is empty right now.
                </div>
"""
        return res
    for filename in images:
        path = os.path.join("../images/", filename)
        cards += f"""
            <div class="col">
                <div class="card shadow-sm">
                    <img src="{path}" class="card-img-top" width="100%" height="225" style="object-fit: cover;">
                    <div class="card-body">
                        <div class="d-flex justify-content-between align-items-center">
                            <div class="d-grid gap-2 d-md-flex justify-content-md-end">
                                <a class="btn btn-outline-primary" href="{path}" role="button">View</a>
                                <form method="post" action="{url}">
                                    <input type="hidden" name="_method" value="DELETE">
                                    <input type="hidden" name="_filename" value="{filename}">
                                    <button type="submit" class="btn btn-outline-secondary" role="button">Delete</button>
                                </form>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        """
    return (cards)
