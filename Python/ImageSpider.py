# -*- coding: utf-8 -*-
# scrapy runspider image.py
import scrapy
from scrapy import Request
from scrapy.linkextractors import LinkExtractor
from scrapy.spiders import CrawlSpider, Rule

import os

class ImageSpider(CrawlSpider):
    name = 'imagespider'
    allowed_domains = ['www.website.com','img.website.com']
    start_urls = ['https://www.website.com/']
    rules = (
        Rule(LinkExtractor(allow=r'https://www.website.com/'), callback='parse_item',follow=True),
        # Rule(LinkExtractor(allow=r'http://img.website.com/*.jpg'), callback='parse_item', follow=False),
    )

    def parse_image(self, response):
        yield self.download(response)
        
    def download(self,response):
        url=response.url
        if not url.startswith('http'):return
        
        filename=url.replace('http://','').replace('https://','')
        filename=filename.replace(':','_').replace('?','_')
        if not filename.endswith('.html'):
            if filename.endswith('/'):filename += 'index.html'
            elif not filename.endswith('.jpg'):filename += '.html'

        path=os.path.dirname(filename)
        if not os.path.exists(path):os.makedirs(path)

        if not os.path.exists(filename):
            with open(filename,'wb') as f:
                f.write(response.body)
                
    def parse_item(self, response):
        # yield self.download(response)
        for src in response.xpath('//img/@src').extract():
            if src.startswith('http'):yield Request(src,callback=self.parse_image)
