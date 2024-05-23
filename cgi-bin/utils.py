#!/usr/bin/python3

from headers import html_head

def generate_response(status, file):
    print (f"HTTP/1.1 {status} \r\nContent-Length: {len(file)}\r\n\r\n{file}")

def generate_html(text):
    return (f"<html>{html_head()}<body>{text}</body></html>")
    
def print_error(path):
    try:
        with open(path, "r") as f:
            generate_response("404 Not found", f.read())
    except OSError:
        generate_response("404 Not found", generate_html("<h1>ERROR: Could not find the specified file</h1>"))