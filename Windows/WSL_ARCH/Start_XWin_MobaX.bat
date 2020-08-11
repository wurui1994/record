REM 计算机\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon
REM UserInit修改为:
REM userinit.exe,cmd /c "<Tht Path>\Start_XWin_MobaX.bat"
REM C:\Windows\system32\userinit.exe,C:\Program Files (x86)\Mobatek\MobaXterm\MobaXterm.exe -hideterm
set PATH=C:\Users\wurui\DOCUME~1\MobaXterm\slash\bin
start XWin_MobaX  -silent-dup-error -notrayicon -nolisten inet6 -hostintitle +bs  -clipboard -nowgl -multiwindow -noreset :0