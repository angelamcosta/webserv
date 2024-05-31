#!/usr/bin/python3

import os
import datetime

def generate_response(status, file, full_path, template=""):
    template = template.replace("{{placeholder}}", file)
    filename = os.path.basename(full_path)
    headers = generate_headers(status, template, filename)
    print(headers + template)

def get_mime_type(filename):
    mime_types = {
        '.html': 'text/html',
        '.css': 'text/css',
        '.js': 'application/javascript',
        '.jpg': 'image/jpeg',
        '.jpeg': 'image/jpeg',
        '.png': 'image/png',
        '.gif': 'image/gif',
    }
    ext = os.path.splitext(filename)[1]
    return(mime_types.get(ext, 'application/octet-stream'))

def generate_headers(status, template, filename):
    headers = f"HTTP/1.1 {status}\r\n"
    current_date = datetime.datetime.utcnow().strftime('%a, %d %b %Y %H:%M:%S GMT')
    headers += f"Date: {current_date}\r\n"
    headers += f"Content-Length: {len(template)}\r\n"
    headers += f"Content-Type: {get_mime_type(filename)}\r\n"
    headers += "\r\n"
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
