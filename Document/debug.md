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

### codelldb
```sh
cd $HOME/.vscode/extensions/vadimcn.vscode-lldb-*/adapter/
# mv codelldb_orig codelldb 
mv codelldb codelldb_orig
cat > codelldb <<EOF
#!/bin/sh
sudo \$HOME/.vscode/extensions/vadimcn.vscode-lldb-*/adapter/codelldb_orig \$@
EOF
chmod +x codelldb
```