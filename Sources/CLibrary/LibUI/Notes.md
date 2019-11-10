# LibUI
```bash
git clone https://github.com/andlabs/libui
cd libui
meson setup build
ninja -C build install
```

## For MacOS:
> error: include file 'stdio.h' not found

Solve:
```bash
tcc -I/usr/include -L. -run file.c
```
		
## For Linux:
```bash
tcc -L. -run file.c
```

## For Windows:
>
1. copy libui.dll to tcc.exe
2. tcc -impdef libui.dll gen libui.def
3. copy libui.def to lib dir.

```bash	
tcc -run file.c
```