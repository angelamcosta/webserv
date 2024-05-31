#!/usr/bin/python3

import os
import uuid
import base64
from utils import generate_response, generate_cards, load_template_file

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
    if os.path.exists(full_path):
        if os.path.isdir(full_path):
            if dir_listing == "on":
                get_directories(full_path, path_info)
            else:
                get_file(path_info + "forbidden.html", path_info, message, "403 Forbidden")
        elif os.path.isfile(full_path):
            get_file(full_path, path_info, message)
    else:
        get_file(error_path, path_info, message, "404 Not found")


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
    generate_response("200 OK", directory_listing_html, path_info + "index.html", template)

def get_file(full_path, path_info, message="", status="200 OK"):
    template = load_template_file(path_info)
    try:
        with open(full_path, "r") as f:
            text = f.read()
        text = text.replace("{{alert}}", message)
        if "{{images}}" in text:
            text = text.replace("{{images}}", generate_cards(path_info + "images"))
        generate_response(status, text, full_path, template)
    except OSError:
        generate_response("404 Not found", "<h1>ERROR: Could not find the specified file</h1>", full_path, template)

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

def get_image(full_path):
    with open(full_path, "rb") as f:
        image_data = f.read()
    generate_response("200 OK", image_data, full_path)