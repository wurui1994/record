jq '.data.video' videoinfo.json
jq '.data|length' videoinfo.json
jq '.data|keys' videoinfo.json
jq '{img:.data.img,video:.data.video}' videoinfo.json
jq '.data|{img:.img,video:.video}' videoinfo.json
jq '.data|[.img,.video]' videoinfo.json
jq '.data|.img,.video' videoinfo.json
jq '.data|keys[0,2]' videoinfo.json
jq '.data.origSubs|length' videoinfo.json

# [] for each.
jq '.data.origSubs[].content' videoinfo.json
jq '.data.origSubs[0]|keys' videoinfo.json

jq 'length' videoinfo.json
jq 'keys' videoinfo.json
jq '.code|type' videoinfo.json
jq '.data|keys' videoinfo.json
jq '.data|.["img","origSubs","video"]|type' videoinfo.json
jq '.data[]|type' videoinfo.json