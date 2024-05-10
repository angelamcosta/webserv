#!/usr/bin/python3

import sys
import os

url = sys.argv[1];
method = sys.argv[2];
filename = sys.argv[3];
full_path = sys.argv[4];
error_page = sys.argv[5];

if (os.path.isfile(full_path)):
    f = open(full_path, "r")
    print(f.read())
    f.close()
else:
    f = open(error_page, "r")
    print(f.read())
    f.close()

# print(url)
# print(method)
# print(filename)
# print(full_path)
# print(error_page)
