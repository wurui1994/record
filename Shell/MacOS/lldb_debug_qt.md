# lldb设置:
```sh
echo "command script import '/Applications/Qt Creator.app/Contents/Resources/debugger/lldbbridge.py'" > ~/.lldbinit
```

# xcode11+设置:
```py
# defaults write com.apple.dt.lldb DefaultPythonVersion 2
# /Applications/Xcode.app/Contents/Developer/usr/bin/pip install pygdbmi
if sys.version_info >= (3, 0):
    binaryvalue = bytes.fromhex(summaryValue)
    return binaryvalue.decode(encoding)
else:
    binaryvalue = summaryValue.decode('hex')
    # LLDB expects UTF-8
    return "\"%s\"" % (binaryvalue.decode(encoding).encode('utf8'))
# string length
self.displayStringLimit = 100
```

# vscode设置:
- lldb设置好后安装codelldb, task manager (optional)
- vscode-cpptools设置`setupCommands`
```json
"setupCommands": [
{
    "description": "Load .lldbinit",
    "text": "command source ~/.lldbinit"
}
```
