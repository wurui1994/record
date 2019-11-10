
#include <opencv2/highgui.hpp>
using namespace cv;

int main()
{
	Mat img = imread("../test.png");
	//namedWindow("Title");
	imshow("title", img);
	waitKey(0);
}