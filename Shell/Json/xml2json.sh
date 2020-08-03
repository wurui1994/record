pip install xmltodict
python -c "import xmltodict, json,sys;print(json.dumps(xmltodict.parse(' '.join(sys.argv[1:]))));" '<e> <a>text</a> <a>text</a> </e>' | jq 
cat test.xml | python -c "import xmltodict, json,sys;print(json.dumps(xmltodict.parse(' '.join(sys.stdin.readlines()))));"|jq '.all'