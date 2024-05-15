#!/usr/bin/python3

import sys
import os

url = sys.argv[1];
method = sys.argv[2];
filename = sys.argv[3];
file_path = sys.argv[4];
error_page = sys.argv[5];

def print_error():
    try:
        with open(error_page, "r") as f:
            print(f.read())
    except OSError:
        print("<h1>ERROR: Could not find the specified file</h1>")

if (os.path.isfile(file_path)):
    try:
        with open(file_path, "r") as f:
            print(f.read())
    except OSError:
        print_error()
else:
    print_error()

# implement methods