# sudo cp /etc/samba/smb.conf.default /etc/samba/smb.conf
# mkdir /home/share
cd home
#chown -R nobody:nobody share/ 不需要
#systemctl start smbd.service nmbd.service
systemctl start smbd nmbd
#security = share

Samba 4 不支持 security = share，可将其去掉或改为 security = user
??? /home/share 可以 /home/wurui/share 不行
最简单的必要形式:
#Global Settings
[global]
map to guest = bad user
guest account = wurui # 用户名 非管理员
#Share Definitions
[share]
path = /home/wurui
read only = No
guest ok = Yes