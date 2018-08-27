import sys
# from lxml import objectify
from copy import deepcopy

from lxml import etree

filename = sys.argv[1]

with open(filename, 'rb') as f:
    data = f.read()
html = etree.XML(data)
namespaces = {'ns': html.nsmap[None]}
result = etree.tostring(html, pretty_print=True)
result = html.xpath('//ns:ItemDefinitionGroup', namespaces=namespaces)
result[1][0] = deepcopy(result[0][0])
result[1][1] = deepcopy(result[0][1])

result[1][0][2].text = result[1][0][2].text.replace('Disabled', 'Full')
result[1][0][3].text = result[1][0][3].text.replace('_DEBUG', 'NDEBUG')
result[1][1][3].text = result[1][1][3].text.replace('debug', 'release')

result[1][1].append(etree.fromstring(
    "<AdditionalOptions>/SAFESEH:NO %(AdditionalOptions)</AdditionalOptions>"))
# html.replace(result[1][0],result[0][0])
prefix = '<?xml version="1.0" encoding="utf-8"?>\n'
# print(type(prefix))
# print(type(etree.tostring(html)))
with open(filename, 'wb') as f:
    f.write(bytes(prefix, 'utf-8')+etree.tostring(html))

# for /f %f in (list.txt) do @python test.py %f
