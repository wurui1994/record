set VlcPath=C:\Users\6#\Documents\Downloads\vlc-2.2.6-win32\vlc-2.2.6
set PATH=%PATH%;%VlcPath%
tcc  -lSDL2 -I%VlcPath%/include -L%VlcPath%/  -lvlc -lvlccore -run  sdl2_test.c mov_bbb.mp4
pause
tcc  -lSDL2 -I%VlcPath%/include -L%VlcPath%/  -lvlc -lvlccore -run  win32_test.c
