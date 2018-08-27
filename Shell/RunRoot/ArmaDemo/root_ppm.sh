root@wurui:# root -l
root [0] .L /usr/lib/libSDL.so
root [1] .L /usr/lib/libSDL_image.so
root [2] .L /usr/lib/libarmadillo.so
root [3]
root [3] .L save_ppm.cpp
root [4] .L show_image.c
root [5] auto filename="test.ppm";
root [6] SavePPM(filename);
root [7] ShowImage(filename);
root [8] SDL_Quit();
root [9]