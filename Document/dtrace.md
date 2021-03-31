```sh
sudo dtrace -l | tr -d '[0-9]' | tr -s ' ' | cut -d ' ' -f2 | sort -u
```