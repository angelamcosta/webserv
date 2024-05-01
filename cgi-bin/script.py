#!/usr/bin/python3

import os
from urllib.parse import parse_qs

query_string = os.environ.get('QUERY_STRING', '')

with open('/home/anlima/webserv/public/index.html', 'r') as file:
    template_content = file.read()

if not query_string:
    html_content = template_content.replace('{{ name }}', 'user')
else:
    params = parse_qs(query_string)
    name = params.get('name', ['default user'])[0]
    html_content = template_content.replace('{{ name }}', name)

print(html_content)
