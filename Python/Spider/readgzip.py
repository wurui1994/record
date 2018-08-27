# -*- coding: utf-8 -*-
import gzip
from io import StringIO
from urllib.request import Request, urlopen

header = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 6.3; WOW64; Trident/7.0; rv:11.0) like Gecko'
}


def webread(url):
    request = Request(url, None, header)
    # request.add_header('Accept-encoding', 'gzip')
    response = urlopen(request)
    if response.info().get('Content-Encoding') == 'gzip':
        buf = StringIO(response.read())
        f = gzip.GzipFile(fileobj=buf)
        data = f.read()
        return data


url = "http://www.website.com/picture.jpg"
open("index.jpg", 'w').write(urlopen(Request(url, None, header)).read())
