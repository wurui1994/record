; -- AppName打包脚本 --
; 该脚本为inno setup脚本,请确保已经安装该软件

[Setup]
AppName=test
AppVersion=1.5
DefaultDirName={src}\test
DefaultGroupName=test
UninstallDisplayIcon={src}\test.exe
Compression=lzma2
SolidCompression=yes
OutputDir=.
OutputBaseFilename=test
UsePreviousAppDir=no

[Files]
Source: "Bin\*.exe"; DestDir: "{app}\Bin"
Source: "Bin\*.dll"; DestDir: "{app}\Bin"
Source: "Bin\*.bat"; DestDir: "{app}"
Source: "Bin\config\*"; DestDir: "{app}\Bin\config"
Source: "Bin\Configuration\*"; DestDir: "{app}\Bin\Configuration"

[Dirs]
Name: "{app}\Bin\Log"

[Run]
Filename: {cmd}; Parameters: "/C Move ""{app}\unins000.exe"" ""{app}\test.exe"""; Flags: RunHidden WaitUntilTerminated
Filename: {cmd}; Parameters: "/C Move ""{app}\unins000.dat"" ""{app}\test.dat"""; Flags: RunHidden WaitUntilTerminated

[UninstallRun]
Filename: {cmd}; Parameters: "/C rmdir /s/q ""{app}\Bin"" "; Flags: RunHidden WaitUntilTerminated

