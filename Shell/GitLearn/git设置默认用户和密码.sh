Shell:
cd ~
echo "https://user_name:password@github.com" > .git-credentials
git config --global user.name "wurui1994"
git config --global user.email 1341531859@qq.com
git config --global credential.helper store

Windows
保存用户名和密码:
解决Git Windows客户端保存用户名和密码的方法，至于为什么，就不想说了。

1. 添加一个HOME环境变量，值为%USERPROFILE%

2. 开始菜单中，点击“运行”，输入“%Home%”并打开目录，并新建“_netrc”文件

3. _netrc文件中输入以下相关内容并保存：
machine github.com
login cnblogs_user
password cnblogs_pwd