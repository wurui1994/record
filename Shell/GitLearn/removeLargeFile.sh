git gc
git count-objects -v
git verify-pack -v .git/objects/pack/pack*.idx | sort -k 3 -n | tail -3
git rev-list --objects --all | grep 0b941a4422235c22787d65d28efaaf59161bb68d
git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch Video/FFMPEG+VSFilter/x86.7z' --prune-empty --tag-name-filter cat -- --all