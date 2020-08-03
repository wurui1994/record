pip install git+https://github.com/vinitkumar/json2xml
python -m src.cli --file=test.json > new.xml
python -m src.cli --file=test.json |xml2json --strip_text | jq '.all' > new.json
python -m src.cli --file=test.json |xml2json --strip_text| jq '.all'

# Add code to cli.py
# parser.add_argument('--stdin', dest='stdin', action='store_true')
#    if args.stdin:
#        import sys
#        str_data = ' '.join(sys.stdin.readlines())
#        data = Json2xml.fromstring(str_data)
#        print(Json2xml.json2xml(data))
cat test.json | python -m src.cli --stdin
cat test.json | python -m src.cli --stdin | xml2json --strip_text| jq '.all'