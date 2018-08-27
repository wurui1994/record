
#include <opencv2/highgui.hpp>
using namespace cv;

int main()
{
	Mat img1, img2, img;
	img1 = imread("test.jpg");
	img2 = imread("test2.png");
	//namedWindow("Title");
	Mat imageROI;
	//
	imageROI = img1(Rect(200, 200, img2.cols, img2.rows));
	addWeighted(imageROI, 0.5, img2, 0.6, 0, imageROI);
	imshow("title", img1);
	waitKey(0);
	imwrite("blend.jpg", img1);
}