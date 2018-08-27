dir $pwd *.ttf | % {if(!(dir C:\Windows\Fonts -name).Contains($_)){(New-Object -ComObject Shell.Application).Namespace(0x14).CopyHere($_.FullName)}}
