from urllib import request

from bs4 import BeautifulSoup

url = "https://www.baidu.com"
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.6) Gecko/20091201 Firefox/3.5.6'}
req = request.Request(url=url, headers=headers)
request = request.urlopen(req)
soup = BeautifulSoup(request.read(), 'lxml')


def child(soup, level, order, l):
    level = level+1
    for node in soup.contents:
        if not node.name:
            continue
        l.append(soup.name + str(level-1)+'_' + str(order) + '->' +
                 node.name + str(level) + '_' + str(soup.contents.index(node)))
        child(node, level, soup.contents.index(node), l)


sideList = []
child(soup, 0, 0, sideList)
outputFile = open('test.dot', 'w')
outputFile.write('digraph G{\n')
outputFile.write('rankdir="LR"\n')
outputFile.write('node[fontname = "Consolas Italic", fontcolor="red",color="cyan"]\n')
outputFile.write('edge [color="green"]\n')
for side in sideList:
    if not sideList.index(side):
        continue
    side = side.replace('[', '').replace(']', '')
    outputFile.write(side+'\n')
outputFile.write('}\n')
outputFile.close()
