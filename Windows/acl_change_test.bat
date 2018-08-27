mkdir test
icacls test
icacls test /grant everyone:F
icacls test /setowner system
icacls test
icacls test /inheritance:d
icacls test
icacls test /remove:g everyone
icacls test /remove "BUILTIN\Users"
icacls test /remove "NT AUTHORITY\Authenticated Users"
icacls test /remove "BUILTIN\Administrators"
icacls test
dir /q /a:d | findstr test
takeown /f test /r /d n
dir /q /a:d | findstr test
icacls test /grant everyone:F
icacls test
icacls test /reset
icacls test
rmdir /s/q test
pause