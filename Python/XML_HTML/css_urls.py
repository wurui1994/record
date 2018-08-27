# -*- coding: utf-8 -*-  
import os
import sys
import lxml.html
import lxml.cssselect


if __name__ == '__main__':
    args = sys.argv
    if len(args) < 3:
        print("Usage:" + args[0] + " file select (attr).")
        print("If attr is empty,print ele content.")
    else:
        if len(args) < 4:
            _,file,select = args
        else:
            _,file,select,attr = args
        
        total = []
        f = open(file)
        urls = f.readlines()
        f.close()

        for index,url in enumerate(urls):
            # print(index,url.strip())
            url = url.strip().replace('https://','').replace('http://','')
            filename = url.replace('?','_').replace('&','_')
            if not os.path.exists(filename):
                # print(url.strip())
                continue
            data = open(filename,'rb').read()
            if len(data) == 0:continue
            eles = lxml.html.fromstring(data).cssselect(select)
        
            if len(args) < 4:
                hrefs = [ele.text for ele in eles]
            else:
                hrefs = [ele.get(attr) for ele in eles] 
            # eles = [ele.text for ele in lxml.html.fromstring(data).cssselect(select)]
            total.extend(hrefs)
        
        for href in total:
            print(href)