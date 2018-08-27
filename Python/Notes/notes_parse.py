import lxml.html
from bs4 import BeautifulSoup

# soup
soup = BeautifulSoup(data,'lxml')
ele = soup.select(css_select)

# lxml
html = lxml.html.fromstring(data)
ele = html.cssselect(css_select)

##examples
def get_hrefs(data,css_select):
    # soup = BeautifulSoup(data,'lxml')
    # ele = soup.select(css_select)
    html = lxml.html.fromstring(data)
    ele = html.cssselect(css_select)
    hrefs = [e for e in ele]
    cell = (hrefs[0].text,hrefs[1].get('href'))
    return cell
    
## lxml 速度是soup的4倍


# re
import re

#
s = 'title=(.*)>(.*)</a>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;下载地址：<a href=\'(.*)\' target'
pattern = re.compile(s.encode('gb2312'))

#
href = pattern.search(data)
href = href.groups()[1:]

#
strings = [k.decode('gb2312') + ' ' + v.decode('gb2312') + '\n' for k,v in total_hrefs]

### 单纯匹配 re比lxml快15倍 100MB/s
# 时间差异,主要是高级库做了额外工作,对少量元素效率不高。
# 少量元素re是合适,解析大多数元素lxml是合适的。
# soup:22*4s lxml:22s re:1.45s