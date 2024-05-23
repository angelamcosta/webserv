HTML = "text/html"
JPEG = "image/jpeg"
PNG = "image/png"
GIF = "image/gif"
TEXT = "text/plain"
FORM = "multipart/form-data"

def html_head():
    header = """
        <head>
            <meta charset="UTF-8" />
            <meta name="viewport" content="width=device-width, initial-scale=1.0" />
            <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" />
            <title>Webserv</title>
        </head>
"""
    return (header)
