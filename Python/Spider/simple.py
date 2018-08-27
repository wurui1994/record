# -*- coding: utf-8 -*-

import os
import re
from urllib import request

from bs4 import BeautifulSoup

# import urllib2


# 定义url
url = 'http://www.website.com'


def urlparse(data, sub):
    # 调用
    # m=urllib2.urlopen(url).read()
    soup = BeautifulSoup(data, 'lxml')
    # print soup.original_encoding
    for a in soup.find_all('a'):
        pic = a.get('href')
        if pic == None:
            continue
        if pic[0] == '#' or pic[0:4] == 'java':
            continue
        elif pic[0:7] == 'http://':
            # print pic
            if pic.endswith('/'):
                filename = pic+'index.html'
            else:
                filename = pic+'/index.html'
            filename = filename.replace('http://', '')
            # filename=filename.replace('/','_');
            # print filename
        else:
            if not pic.startswith('/'):
                sub = sub.replace('http://', '')
                # print sub,'----'
                subpath = sub.split('/')
                # print sub,'----'
                subpath = '/'.join(subpath[0:-1])
                pic = 'http://'+subpath+'/'+pic
            else:
                pic = url+pic
            if not pic.endswith('.html'):
                filename = pic+'index.html'
            else:
                filename = pic
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
            link = request.urlopen(pic)
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
    for src in soup.find_all('img'):
        srcUrl = src.get('src')
        # print pic
        if srcUrl == None:
            continue
        if srcUrl[0] == '#' or srcUrl[0:4] == 'java':
            continue
        else:
            if not srcUrl.startswith('/'):
                print(srcUrl)
            else:
                srcUrl = url + srcUrl
            filename = srcUrl
            # filename=url+filename
            filename = filename.replace('http://', '')
            filename = filename.replace('?', '_')
        # print pic,' '+filename
        path = filename.split('/')
        path = '/'.join(path[0:-1])
        if not os.path.exists(path):
            os.makedirs(path)
        # if os.path.exists(filename):continue
        # try:
           # link=urllib2.urlopen(pic)
        # except: print filename+' timeout';continue
        filelist = open('imagelist.txt', 'a+')
        filelist.write(filename+'\n')
        filelist.close()
        # print filename
        # if link:
        # ff=open(filename,'wb')
        # try:
        # buffer=link.read()
        # except:print 'fail';continue
        # ff.write(buffer)
        # ff.close()


m = request.urlopen(url).read()
urlparse(m, url)
# f=open('urllist.txt','r')
# for x in f.readlines():
# if not x:print 'None';continue
# print x
# print '--------------------------------------------'
# data=open(x[0:-1]).read()
# urlparse(data,x[0:-1])
# for x in f.readlines():
# print x
# print '--------------------------------------------'
# data=open(x[0:-1]).read()
# urlimage(data)
