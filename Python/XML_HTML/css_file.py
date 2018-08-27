# -*- coding: utf-8 -*-  
import sys

import lxml.html
import lxml.cssselect

def main():
    args = sys.argv
    if len(args) < 3:
        print("Usage:" + args[0] + " url select (attr).")
        print("If attr is empty,print ele content.")
    else:
        # print(args)
        if len(args) < 4:
            _,url,select = args
        else:
            _,url,select,attr = args

        url = url.strip().replace('https://','').replace('http://','')
        filename = url.replace('?','_').replace('&','_')
        data = open(filename,'rb').read()
        # print(data)
        eles = lxml.html.fromstring(data).cssselect(select)
        
        if len(args) < 4:
            hrefs = [ele.text for ele in eles]
        else:
            hrefs = [ele.get(attr) for ele in eles] 
            
        for href in hrefs:
            print(href)
            
if __name__ == '__main__':
    main()