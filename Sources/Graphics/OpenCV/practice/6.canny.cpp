#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

int main()
{
	Mat img = imread("blend.jpg", 0);
	//namedWindow("Title");
	Canny(img, img, 100, 100);
	imshow("title", img);
	waitKey(0);
}