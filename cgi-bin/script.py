#!/usr/bin/python3

import cgi

form = cgi.FieldStorage()
name = form.getvalue('name', 'deafult user')

with open('/home/anlima/webserv/public/index.html', 'r') as file:
    template_content = file.read()

html_content = template_content.replace('{{ name }}', name)

print(html_content)
