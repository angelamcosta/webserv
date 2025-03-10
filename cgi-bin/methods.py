#!/usr/bin/python3

import os
import sys
import uuid
import base64
import imghdr
from utils import generate_response, generate_cards, load_template_file, generate_headers


def success_upload():
    message = """
        <div class="alert alert-success mt-3" role="alert">
            File uploaded successfully!
        </div>
"""
    return message


def upload_failed():
    message = """
        <div class="alert alert-danger mt-3" role="alert">
            File upload failed.
        </div>
"""
    return message


def file_missing():
    message = """
        <div class="alert alert-warning mt-3" role="alert">
            No file field found in the form.
        </div>
"""
    return message


def success_delete():
    message = """
        <div class="alert alert-success mt-3" role="alert">
            File delete successfully!
        </div>
"""
    return message


def delete_failed(file):
    message = f"""
        <div class="alert alert-danger mt-3" role="alert">
            File delete failed.
        </div>
"""
    return message


def handle_get(full_path, dir_listing, error_path, path_info, url, message=""):
    if message == "invalid_size":
        message = upload_failed()
        get_file(full_path, path_info, url, message, status="413 Request Entity Too Large")
    elif os.path.exists(full_path):
        if os.path.isdir(full_path):
            if dir_listing == "on":
                get_directories(full_path, path_info)
            else:
                get_file(path_info + "forbidden.html", path_info,
                         url, message, "403 Forbidden")
        elif os.path.isfile(full_path):
            if full_path.endswith(('.png', '.jpg', '.jpeg', '.gif')):
                get_image(full_path, path_info, error_path, url)
            else:
                get_file(full_path, path_info, url, message)
    else:
        get_file(error_path, path_info, url, message, "404 Not found")


def get_directories(full_path, path_info):
    template = load_template_file(path_info)
    arr = os.listdir(full_path)
    file_list = "\n".join([f"<li>{file}</li>" for file in arr])
    directory_listing_html = f"""<div class="container">
                <div class="row">
                    <div class="col-md-12">
                        <div class="error-template">
                            <h1>{full_path}</h1>
                            <div class="error-details">
                                <ul>{file_list}</ul>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
    """
    generate_response("200 OK", directory_listing_html,
                      path_info + "index.html", template)


def get_file(full_path, path_info, url, message="", status="200 OK"):
    template = load_template_file(path_info)
    try:
        with open(full_path, "r", encoding="iso-8859-1") as f:
            text = f.read()
        text = text.replace("{{alert}}", message)
        if "{{images}}" in text:
            text = text.replace("{{images}}", generate_cards(
                path_info + "images", url))
        generate_response(status, text, full_path, template)
    except OSError:
        generate_response(
            "404 Not found", "<h1>ERROR: Could not find the specified file" + path_info +"</h1>", full_path, template)


def handle_post(upload_dir, image_data):
    if not image_data:
        return file_missing()
    binary_image_data = base64.b64decode(image_data)
    extension = imghdr.what(None, binary_image_data)
    if not extension:
        return upload_failed()
    filename = str(uuid.uuid4()) + '.' + extension
    with open(upload_dir + filename, 'wb') as f:
        f.write(binary_image_data)
    return success_upload()


def get_image(full_path, path_info, error_path, url, message="", status="200 OK"):
    try:
        with open(full_path, "rb") as f:
            content = f.read()

        filename = os.path.basename(full_path)
        content_length = os.path.getsize(full_path)
        if len(content) != content_length:
            get_file(error_path, path_info, url, message, "404 Not found")
            return
        headers = generate_headers(status, content_length, filename)
        sys.stdout.buffer.write(headers.encode())
        sys.stdout.buffer.write(b"\r\n")
        sys.stdout.buffer.write(content)
    except OSError:
        get_file(error_path, path_info, url, message, "404 Not found")


def handle_delete(url, upload_dir, filename):
    try:
        os.remove(upload_dir + filename)
        return success_delete()
    except OSError:
        return delete_failed(url)
