from requests_html import HTMLSession
HTMLSession().get("https://www.website.com/").html.xpath("//ul[@class='img']/li/a/@href")
