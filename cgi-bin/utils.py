#!/usr/bin/python3

import os

def generate_response(status, file, path_info, full_path):
    filename = os.path.basename(full_path)
    if isinstance(file, str):
        template = load_template_file(path_info)
        template = template.replace("{{placeholder}}", file)
        print(f"HTTP/1.1 {status} \r\nContent-Length: {len(template)}\r\nContent-Type: {get_mime_type(filename)}\r\n\r\n{template}")
    else:
        res = f"HTTP/1.1 {status} \r\nContent-Length: {len(file)}\r\nContent-Type: {get_mime_type(filename)}\r\n\r\n"
        print(res.encode('utf-8') + file)

    
def print_error(path, path_info, full_path):
    try:
        with open(path, "r") as f:
            generate_response("404 Not found", f.read(), path_info, full_path)
    except OSError:
        generate_response("404 Not found", "<h1>ERROR: Could not find the specified file</h1>", path_info, full_path)

def get_upload_dir(path_info):
    upload_dir = path_info + "images/" if path_info[-1] == "/" else path_info + "/images/"
    return upload_dir

def get_full_path(url, path_info, index):
    if ".py" in url:
        full_path = path_info + index if path_info[-1] == "/" else path_info + "/" + index
    elif (path_info[-1] == "/" and url[0] == "/"):
        full_path = path_info + url[1:]
    elif (path_info[-1] == "/" and url[0] != "/") or (path_info[-1] != "/" and url[0] == "/"):
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