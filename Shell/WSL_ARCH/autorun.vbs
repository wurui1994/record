' set ws=WScript.CreateObject("WScript.Shell")
' CurrentPath =  createobject("Scripting.FileSystemObject").GetFolder(".").Path & "\Start_XWin_MobaX.bat" 
' Command="cmd /c " &  Chr(34) & CurrentPath &  Chr(34)
' msgbox Command 
' ws.Run Command,0

' C:\Windows\system32\userinit.exe,wscript C:\Users\Public\autorun.vbs
set ws=WScript.CreateObject("WScript.Shell")
Command=Chr(34) & "C:\Program Files (x86)\Mobatek\MobaXterm\MobaXterm.exe -hideterm" &  Chr(34)
' msgbox Command 
ws.Run Command,0