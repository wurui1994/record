REM pconvert.exe -monochrome csdn5.png code.jpg
REM @set TESSDATA_PREFIX=D:\Software\MSYS2\mingw32\share
@tesseract 1357042419_3300.jpg result -l eng
@cls
@type result.txt
@pause
@del *.txt