xmllint --html --xpath "//a/@href" index.html 2>NUL | sed 's/ href=/\n/g' | sed 's/\"//g'

xmllint --html --xpath "//a/img/@src" index.html | sed "s/ /\n/g"|cut -d'"' -f2