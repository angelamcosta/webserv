#!/usr/bin/python3

import os
import cgi
import cgitb
from utils import generate_response, generate_html, print_error

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

def handle_get(full_path, dir_listing, error_path, message=""):
    if os.path.isdir(full_path):
        if dir_listing == "on":
            arr = os.listdir(full_path)
            file_list = "\n".join([f"<li>{file}</li>" for file in arr])
            directory_listing_html = f"<h1>{full_path}</h1><ul>{file_list}</ul>"
            generate_response("200 OK", generate_html(directory_listing_html))
        else:
            generate_response("403 Forbidden", generate_html("<h1>ERROR: You don't have permission to access this page.</h1>"))
    elif os.path.isfile(full_path):
        with open(full_path, "r") as f:
            text = f.read()
        text = text.replace("{{placeholder}}", message)
        generate_response("200 OK", text)
    else:
        print_error(error_path)

def handle_post(upload_dir, full_path, dir_listing, error_path):
    cgitb.enable()
    form = cgi.FieldStorage()
    if 'file' not in form:
        handle_get(full_path, dir_listing, error_path, file_missing())
        return
    fileitem = form['file']
    if not fileitem.file:
        handle_get(full_path, dir_listing, error_path, file_missing())
        return
    if not fileitem.filename:
        return
    filename = fileitem.filename
    filepath = os.path.join(upload_dir, filename)
    if os.path.isdir(filepath):
        with open(filepath, 'wb') as f:
            f.write(fileitem.file.read())
        handle_get(full_path, dir_listing, error_path, success_upload())
    else:
        handle_get(full_path, dir_listing, error_path, dir_missing())      

def not_allowed():
    generate_response("405 Not Allowed", generate_html(f"<h1>ERROR: Method not allowed.</h1>"))