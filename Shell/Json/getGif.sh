# jq '."0"[1]' emotion.json
for f in `seq 0 34`
do 
query=$(echo -n \'.\"$f\"[0]\')
# echo $query
cmd=$(echo -n "jq $query emotion.json")
eval $cmd
query=$(echo -n \'.\"$f\"[1]\')
# echo $query
cmd=$(echo -n "jq $query emotion.json")
eval $cmd|cut -d "," -f 2|sed "s/\"//g"|base64 -d > $f.gif
done
