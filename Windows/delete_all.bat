@echo off
DEL /F /A /Q \\?\%1  
RD /S /Q \\?\%1
echo. & pause 