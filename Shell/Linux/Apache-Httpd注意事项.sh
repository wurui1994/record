# Windows http://www.apachelounge.com/
#1.文件conf/http.conf:
# .. or /
ServerRoot ".."
Listen 80
ServerName localhost:80

LoadModule dav_module modules/mod_dav.so
LoadModule dav_fs_module modules/mod_dav_fs.so

<Directory />
    AllowOverride none
    Require all granted
</Directory>

DocumentRoot "./htdocs"
<Directory "./htdocs">
    Options Indexes FollowSymLinks
    AllowOverride None
    Require all granted
</Directory>

Include conf/extra/httpd-dav.conf

Alias /download "./htdocs/download"
<Directory "./htdocs/download">
    Options Indexes
    AllowOverride None
    Order allow,deny
    Allow from all
    Require all granted
</Directory>

#2.文件conf/extra/httpd-dav.conf:
#建立./var/DavLock文件
DavLockDB "./var/DavLock"

Alias /uploads "./htdocs/uploads"

<Directory "./htdocs/uploads">
    Dav On
    
    Options Indexes
    AllowOverride None
    Order allow,deny
    Allow from all
    # AuthType Basic
    # AuthType Digest
    AuthName DAV-upload
    # You can use the htdigest program to create the password database:
    #   htdigest -c "c:/Apache24/user.passwd" DAV-upload admin
    # AuthUserFile "E:/HttpServer/Apache24/user.passwd"
    # AuthDigestProvider file

    # Allow universal read-access, but writes are restricted
    # to the admin user.
    # <RequireAny>
        # Require method GET POST OPTIONS
        # Require user admin
    # </RequireAny>
    # Require valid-user
</Directory>