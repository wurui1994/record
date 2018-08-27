wmic process where processid="7980" get CommandLine

wmic process where name="x264.exe" get CommandLine

wmic process where name="avs4x26x.exe" get CommandLine

powershell -c "Get-WmiObject Win32_Process -Filter "name = '$process'" | select CommandLine"