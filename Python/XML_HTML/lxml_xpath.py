from lxml.html import fromstring
from requests import get
# [e.get('href') for e in fromstring(get('http://website.com').text).cssselect('a[href]')]
fromstring(get("https://www.website.com/").content).xpath("//ul[@class='img']/li/a/@href")
