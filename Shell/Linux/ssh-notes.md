# VS code ssh免密登陆
* 1.windows下用ssh-keygen 生成公钥和秘钥（使用git Bash Here）

    使用命令 ssh-keygen.exe -t rsa （可以一路Enter）

* 2.将公钥发送到服务器

    `ssh-copy-id -i .ssh/id_rsa.pub user@192.168.1.110`, 此时会要求输一次服务器密码

* 3.vscode插件Remote Development如果已经配置好对应的服务器，那么下次再ssh登陆时，就不用输密码了

    另外，我vscode ssh的配置文件ssh_config路径C:\Users\Administrator\.ssh，生成公钥私钥放的位置也在这儿