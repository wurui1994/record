# list dshow devices
ffplay -f dshow -i dummy -list_devices true 2>&1|findstr dshow
# Camera with dshow
ffplay -f dshow -i video="Camera"
# Screen Record use gdigrab
ffplay -f gdigrab -i desktop -video_size 1280x720
# mandelbrot
ffplay -f lavfi -i mandelbrot
# render subtitle without video
ffplay -f lavfi -i color=s=1289x720 -vf subtitles=test.ass
ffplay -f lavfi -i nullsrc=s=1280x720,geq=r=0:g=0:b=0 -vf subtitles=test.ass
ffplay -f lavfi -i nullsrc=s=1280x720,geq=random(1)*255:128:128 -vf subtitles=test.ass
# set video time for subtitle
ffplay -f lavfi -i "color=size=1280x720,trim=6:60" -vf subtitles=test.ass
# use AviSynth
ffplay -i test.avs
ffplay -f avisynth test.avs
# cut video
ffmpeg -i test.mkv -ss 0 -t 60 -c copy part1.mkv -ss 60 -t 60 -c copy part2.mkv
# multi subtitle
ffplay -f lavfi -i color=s=1289x720 -vf subtitles=test1.ass,subtitles=test2.srt,scale=1280:720

# watermark origin
ffplay -f lavfi "movie=test.mkv,subtitles=test.ass,scale=1280:720[mainvideo]; movie=test.png [watermark]; [mainvideo][watermark] overlay[out0];amovie=test.mkv[out1]"

ffmpeg -i test.mkv -vf "[0:v]subtitles=test.ass,scale=1280:720[mainvideo];movie=test.png [watermark];[mainvideo][watermark]overlay" test_new.mkv

# watermark simple
ffplay -i test.mkv -vf "subtitles=test.ass,scale=1280:720[mainvideo];movie=test.png [watermark];[mainvideo][watermark]overlay"

ffmpeg -i test.mkv -vf "subtitles=test.ass,scale=1280:720[mainvideo];movie=test.png [watermark];[mainvideo][watermark]overlay" test_new.mkv

ffplay -i test.mkv -vf "setpts=PTS/8.0,scale=1280:720" -af "atempo=2.0,atempo=2.0,atempo=2.0"