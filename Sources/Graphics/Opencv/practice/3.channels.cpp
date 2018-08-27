
#include <vector>
#include <opencv2/highgui.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat img;
	vector<Mat> channels;
	img = imread("test.jpg");
	split(img, channels);
	//channels.at(0)=0;
	channels.at(1) = 0;
	channels.at(2) = 0;
	merge(channels, img);
	imshow("title", img);
	waitKey(0);
}