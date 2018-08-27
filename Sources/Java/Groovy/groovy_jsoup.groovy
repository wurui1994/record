//For groovysh
// groovy.grape.Grape.grab(group:"org.jsoup", module:"jsoup", version:"1.11.1")
//For groovy
@Grab(group="org.jsoup", module="jsoup", version="latest.release")

import org.jsoup.Jsoup;
// Jsoup.connect("http://cnblogs.com").get().select("#post_list > div > div.post_item_body > h3 > a").each {
    // println it.text()
// }
hrefs = Jsoup.connect("http://cnblogs.com").get().select('a[href]').collect{it.attr('href')};
println(hrefs)


// # Python version:
// from lxml.html import fromstring
// from requests import get
// # [e.get('href') for e in fromstring(get('http://cnblogs.com').text).cssselect('a[href]')]
// fromstring(get('http://cnblogs.com').text).xpath('//a/href')
