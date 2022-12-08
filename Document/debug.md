## Debug as root
### /etc/sudoers
```sh
# sudo tail -f /etc/sudoers
%admin ALL = (ALL) NOPASSWD: ALL
```

### lldbasroot
```json
"miDebuggerPath" :"${workspaceFolder}/lldbasroot",
```
```sh
#!/bin/sh
sudo $HOME/.vscode/extensions/ms-vscode.cpptools-*/debugAdapters/lldb-mi/bin/lldb-mi $@
# ls $HOME/.vscode/extensions/ms-vscode.cpptools-*/debugAdapters/lldb-mi/bin/lldb-mi
```

### gdbasroot
```json
"miDebuggerPath" :"${workspaceFolder}/gdbasroot",
```
```sh
#!/bin/sh
sudo /usr/bin/gdb $@
```
