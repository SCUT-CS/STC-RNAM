#include "Headers.h"
#include "Calculate.h"
pair<double, double> testPSNR()
{
	string image_path1 = samples::findFile("../Project1/gray_images/1_gray256.bmp");
	Mat img1 = imread(image_path1, 0);
	Mat imggest1 = Mat::zeros(img1.size(), img1.type());
	double res1 = PSNR(img1, imggest1);

	string image_path2 = samples::findFile("../Project1/gray_images/bigbuildingzyp256.bmp");
	Mat img2 = imread(image_path2, 0);
	Mat imggest2 = Mat::zeros(img2.size(), img2.type());
	double res2 = PSNR(img2, imggest2);
	
	return make_pair(res1, res2);
}