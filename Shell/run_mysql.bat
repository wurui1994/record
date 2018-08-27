cd /d %~dp0
cd bin
net stop MySQL
mysqld remove
rd /s/q ..\data

mysqld --initialize-insecure --console
start mysqld --console
mysql -uroot
REM mysqld install
REM net start MySQL
REM mysql
pause