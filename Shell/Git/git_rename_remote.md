
# git-renaming-branches-remotely

## First checkout to the branch which you want to rename

```sh
git branch -m old_branch new_branch
git push -u origin new_branch
```

## To remove old branch from remote:

```sh
git push origin :old_branch
```

