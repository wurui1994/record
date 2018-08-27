// tcc -lavformat -run videosize.c video.mp4
#include <libavformat/avformat.h>

int main(int argc,const char* argv[])
{
	const char* filename = argv[1];
	//
    av_register_all();
    AVFormatContext* ctx = avformat_alloc_context();
    if(avformat_open_input(&ctx,filename,NULL,NULL) != 0) return -1;  
    if(avformat_find_stream_info(ctx,NULL) < 0) return -1;  
	int vstream_index = av_find_best_stream(ctx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
	AVStream* vstream = ctx->streams[vstream_index];
	AVCodecParameters* vparam = vstream->codecpar;
	printf("%d %d\n",vparam->width,vparam->height);
    return 0;
}