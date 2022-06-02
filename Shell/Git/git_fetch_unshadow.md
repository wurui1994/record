https://www.delenamalan.co.za/2019/fetch-all-branches.html
```bash
git clone --detph 1 <url.git>
git fetch --depth 1000
git fetch --unshallow
git config remote.origin.fetch
git config remote.origin.fetch "+refs/heads/*:refs/remotes/origin/*"
git remote update
git fetch --unshallow
```