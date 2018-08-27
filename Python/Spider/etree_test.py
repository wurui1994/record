from lxml import etree

tree = etree.parse('sitemap.xml')

locs = tree.xpath("//url//loc")
# print(locs)
hrefs = [loc.text + '\n' for loc in locs]

file = open('item3.txt', 'w')
file.writelines(hrefs)
file.close()
