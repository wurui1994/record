# -*- coding: utf-8 -*-

import os
import re
# import urllib2
from urllib.request import urlopen

from bs4 import BeautifulSoup

# 定义百度函数
url = 'http://www.website.com'


def urlparse(data, sub):
    # 调用
    # m=urllib2.urlopen(url).read()
    soup = BeautifulSoup(data, 'lxml')
    # print soup.original_encoding
    for a_tag in soup.find_all('a'):
        href = a_tag.get('href')
        if href == None:
            continue
        if href[0] == '#' or href[0:4] == 'java':
            continue
        elif href[0:7] == 'http://':
            # print pic
            if href.endswith('/'):
                filename = href + 'index.html'
            else:
                filename = href + '/index.html'
            filename = filename.replace('http://', '')
            # filename=filename.replace('/','_');
            # print filename
        else:
            if not href.startswith('/'):
                sub = sub.replace('http://', '')
                # print sub,'----'
                subpath = sub.split('/')
                # print sub,'----'
                subpath = '/'.join(subpath[0:-1])
                href = 'http://'+subpath+'/'+href
            else:
                href = url+href
            if not href.endswith('.html'):
                filename = href+'index.html'
            else:
                filename = href
            # filename=url+filename
            filename = filename.replace('http://', '')
            filename = filename.replace('?', '_')
        filename = filename.replace(' ', '_')
        # print filename
        if filename.find('website.com') == -1:
            continue
        path = filename.split('/')
        path = '/'.join(path[0:-1])
        if not os.path.exists(path):
            os.makedirs(path)
        if os.path.exists(filename):
            continue
        try:
            link = urlopen(href)
        except:
            print(filename+' timeout')
            continue
        filelist = open('urllist.txt', 'a+')
        filelist.write(filename+'\n')
        filelist.close()
        # print filename
        if link:
            ff = open(filename, 'wb')
            try:
                buffer = link.read()
            except:
                print('fail')
                continue
            ff.write(buffer)
            ff.close()


def urlimage(data):
    # 调用
    # m=urllib2.urlopen(url).read()
    soup = BeautifulSoup(data, 'lxml')
    # print soup.original_encoding
    for img in soup.find_all('img'):
        src = img.get('src')
        # print pic
        if src == None:
            continue
        if src[0] == '#' or src[0:4] == 'java':
            continue
        else:
            if not src.startswith('/'):
                print(src)
            else:
                src = url+src
            filename = src
            # filename=url+filename
            filename = filename.replace('http://', '')
            filename = filename.replace('?', '_')
        # print pic,' '+filename
        path = filename.split('/')
        path = '/'.join(path[0:-1])
        if not os.path.exists(path):
            os.makedirs(path)
        if os.path.exists(filename):
            continue
        try:
            link = urlopen(src)
        except:
            print(filename+' timeout')
            continue
        # filelist=open('imagelist.txt','a+')
        # filelist.write(filename+'\n');
        # filelist.close();
        print(filename)
        if link:
            ff = open(filename, 'wb')
            try:
                buffer = link.read()
            except:
                print('fail')
                continue
            ff.write(buffer)
            ff.close()


# m=urllib2.urlopen(url).read()
# urlparse(m)
# urlparse(url)
f = open('urllist.txt', 'r')
# for x in f.readlines():
# if not x:print 'None';continue
# print x
# print '--------------------------------------------'
# data=open(x[0:-1]).read()
# urlparse(data,x[0:-1])
for line in f.readlines():
    print(line)
    print('--------------------------------------------')
    data = open(line.rstrip()).read()
    urlimage(data)
