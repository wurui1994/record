# seq 4|parallel -n0 -j4 -u "curl -I www.baidu.com"
#
for f in {1..37}
do
url="http://www.tutu12345.cc/a/cn/xiuren/list_6_$f.html"
echo $url
curl -s $url  | xmllint --format --html --xpath '/html/body/div[2]/div[4]/ul/li/a/@href' - 2>/dev/null | sed -e 's/href=\"//g' -e 's/\"/\n/g' | tr -d ' ' | grep http>> list.txt
done
#
cat list.txt | parallel -j0 "curl -s {} | xmllint --format --html --xpath '/html/body/p[3]/a[2]/@href' - 2>/dev/null | sed -e 's/href=\"//g' -e 's/\"/\n/g' | tr -d ' ' | grep http >> urls.txt"
cat urls.txt | parallel -j0 "curl -I {} |grep Location|sed 's/Location: //g' >> files.txt"
dos2unix files.txt
# cat files.txt | parallel --bar -u -j0 wget -c
aria2c -x 16 -i files.txt