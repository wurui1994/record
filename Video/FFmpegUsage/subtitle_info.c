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
	for(int i = 0; i < ctx->nb_streams; ++i)
	{
		if(ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_SUBTITLE)
		{
			if(ctx->streams[i]->codec->codec_id == AV_CODEC_ID_SRT)
			{
				printf("subtitle srt.\n");
			}
			else if(ctx->streams[i]->codec->codec_id == AV_CODEC_ID_ASS)
			{
				printf("subtitle ass.\n");
			}
			else if(ctx->streams[i]->codec->codec_id == AV_CODEC_ID_SUBRIP)
			{
				printf("subtitle subrip.\n");
			}
			else
			{
				printf("subtitle %d.\n",ctx->streams[i]->codec->codec_id);
			}
			AVDictionaryEntry *tag = av_dict_get(ctx->streams[i]->metadata, "language", NULL, 0);
			if (!tag)
				tag = av_dict_get(ctx->streams[i]->metadata, "lang", NULL, 0);
			if (tag) {
				printf("lang=%s\n",tag->value);
			}
		}
		
		// AVDictionaryEntry *tag = av_dict_get(ctx->streams[i]->metadata, "language", NULL, 0);
		// if (!tag)
			// tag = av_dict_get(ctx->streams[i]->metadata, "lang", NULL, 0);
		// if (tag) {
			// printf("lang=%s\n",tag->value);
		// }
	}
    return 0;
}