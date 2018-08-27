// tcc -lavformat -run output_formats.c
// ref:https://stackoverflow.com/questions/2940521/where-to-get-full-list-of-libav-formats
#include <libavformat/avformat.h>

int main(int argc,const char* argv[])
{
	av_register_all();
	AVOutputFormat * oformat = av_oformat_next(NULL);
	while(oformat != NULL)
	{
		fprintf(stderr, "{\"%s\",\"%s\"},\n", 
			oformat->name,oformat->extensions);
		oformat = av_oformat_next(oformat);
	}
	return 0;
}
    