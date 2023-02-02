# test
```sh
log stream --predicate 'senderImagePath CONTAINS "hello"'
# log show --predicate 'senderImagePath CONTAINS "hello"'
```
```sh
$ cd ~
$ which
-bash: /usr/bin/which: Operation not permitted
$ mkdir macf_read_deny
$ cd macf_read_deny/
$ echo hello > test.txt
$ cat test.txt
cat: test.txt: Operation not permitted
$ cd ~
$ mkdir macf_read_deny
$ cd macf_read_deny/
$ echo hello > test.txt
$ cat test.txt
cat: test.txt: Operation not permitted
```
