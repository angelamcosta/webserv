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
    upload_dir = path_info + "images/" if path_info[-1] == "/" else path_info + "/images/"
    return upload_dir

def get_full_path(url, path_info, index):
    if ".py" in url:
        full_path = path_info + index if path_info.endswith("/") else path_info + "/" + index
    elif url.startswith("/") and path_info.endswith("/"):
        full_path = path_info + url[1:]
    elif url.startswith("/") or path_info.endswith("/"):
        full_path = path_info + url
    else:
        full_path = path_info + "/" + url
    return full_path

def load_template_file(path_info):
    path_info = path_info + "template.html" if path_info[-1] == "/" else path_info + "/template.html"
    with open(path_info, 'r') as f:
        template = f.read()
    return (template)

def generate_cards(directory):
    images = os.listdir(directory)
    cards = ''
    if not images:
        res = """<div class="alert alert-secondary" role="alert">
                    The pond is empty right now.
                </div>
"""
        return res
    for filename in images:
        path = os.path.join("/images/", filename)
        cards += f"""
            <div class="col">
                <div class="card shadow-sm">
                    <img src="{path}" class="bd-placeholder-img card-img-top" width="100%" height="225">
                    <div class="card-body">
                        <div class="d-flex justify-content-between align-items-center">
                            <div class="btn-group">
                                <button type="button" class="btn btn-sm btn-outline-secondary">View</button>
                                <button type="button" class="btn btn-sm btn-outline-secondary">Delete</button>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        """
    return (cards)
