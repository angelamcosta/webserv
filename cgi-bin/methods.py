#!/usr/bin/python3

import os
import uuid
import base64
from utils import generate_response, print_error, generate_cards

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

def dir_missing():
    message = """
        <div class="alert alert-light mt-3" role="alert">
            The server couldn't find a directory to save the images to.
        </div>
"""
    return message

def handle_get(full_path, dir_listing, error_path, path_info, message=""):
    if os.path.isdir(full_path):
        if dir_listing == "on":
            arr = os.listdir(full_path)
            file_list = "\n".join([f"<li>{file}</li>" for file in arr])
            directory_listing_html = f"<h1>{full_path}</h1><ul>{file_list}</ul>"
            generate_response("200 OK", directory_listing_html, path_info, full_path)
        else:
            generate_response("403 Forbidden", "<h1>ERROR: You don't have permission to access this page.</h1>", path_info, full_path)
    elif os.path.isfile(full_path):
        if full_path.endswith(('.png', '.jpg', '.jpeg', '.gif')):
            with open(full_path, "rb") as f:
                image_data = f.read()
            generate_response("200 OK", image_data, path_info, full_path)
        else:
            with open(full_path, "r") as f:
                text = f.read()
            text = text.replace("{{alert}}", message)
            if "{{images}}" in text:
                text = text.replace("{{images}}", generate_cards(path_info + "images"))
            generate_response("200 OK", text, path_info, full_path)
    else:
        print_error(error_path, path_info, full_path)

def handle_post(upload_dir, image_data):
    if not image_data:
        return file_missing()
    filename = str(uuid.uuid4()) + '.jpg'
    binary_image_data = base64.b64decode(image_data)
    with open(upload_dir + filename, 'wb') as f:
        f.write(binary_image_data)
    return success_upload()

def not_allowed(path_info, full_path):
    generate_response("405 Not Allowed", f"<h1>ERROR: Method not allowed.</h1>", path_info, full_path)