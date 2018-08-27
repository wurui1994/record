# For ffmpeg 3.4.1
# https://git.ffmpeg.org/gitweb/ffmpeg.git/tree/refs/heads/release/3.4:/fftools
# The `config.h` is modified from 
# https://github.com/ShiftMediaProject/FFmpeg/blob/master/SMP/config.h [0808351 Jan 8, 2018]
gcc  -lm -I/usr/include/SDL2 -lSDL2 -lavutil -lavformat -lavcodec -lswresample -lavdevice -lavfilter -lswscale  -lpostproc cmdutils.c ffplay.c -o ffplay -w

gcc  -lm -lavutil -lavformat -lavcodec -lswresample -lavdevice -lavfilter -lswscale  -lpostproc cmdutils.c ffmpeg.c ffmpeg_hw.c ffmpeg_opt.c ffmpeg_filter.c ffmpeg_cuvid.c -o ffmpeg -w