# -*- coding: utf-8 -*-

from urllib.request import urlopen

from bs4 import BeautifulSoup

# 定义百度函数
host = 'http://www.website.com'
url = host+'/path'


def urlparse(data, sub):
    soup = BeautifulSoup(data, 'lxml')
    ff = open('test.dot', 'w')
    ff.write('digraph G{\n')
    ff.write('rankdir=LR\n')
    ff.write('node[fontname="Consolas Italic",color=cyan]\n')
    ff.write('edge[color=green]\n')
    for a_tag in soup.find_all('a'):
        href = a_tag.get('href')
        # print pic
        if href == None:
            continue
        if href[0] == '#' or href[0:4] == 'java':
            continue
        elif href[0:7] == 'http://' or href[0:8] == 'https://':
            # print pic
            if href.endswith('/'):
                filename = href+'index.html'
            else:
                filename = href+'/index.html'
            # filename=filename.replace('http://','');
        else:
            if not href.startswith('/'):
                sub = sub.replace('http://', '')
                subpath = sub.split('/')
                subpath = '/'.join(subpath[0:-1])
                href = subpath+'/'+href
            else:
                href = host+href
            if not href.endswith('.html'):
                filename = href+'index.html'
            else:
                filename = href
            # filename=host+filename
        # print filename
        filename = filename.replace('https://', '').replace('http://', '')
        print(filename)
        sub = sub.replace('http://', '')
        for a_tag in '.%/':
            sub = sub.replace(a_tag, '_')
        for a_tag in '.%/&=-? ':
            filename = filename.replace(a_tag, '_')
        ff.write(sub+'->'+filename+'\n')
    ff.write('}\n')
    ff.close()


# f=open('hostlist.txt','r')
# lines=f.readlines()
# for x in lines[0:1]:
    # if not x:print 'None';continue
    # data=open(x[0:-1]).read()
    # hostparse(data,x[0:-1])
data = urlopen(url).read()
urlparse(data, url)
