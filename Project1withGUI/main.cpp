#include "Project1.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Project1 w;
    w.show();
    return a.exec();

}

//#include <iostream>  
//#include <opencv2\imgproc\types_c.h>
//#include<opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>  
//#include <opencv2/highgui/highgui.hpp>  
//#include <opencv2/imgproc/imgproc.hpp>  
//using namespace cv;
//int main()
//{
//
//	Mat img = imread("C:/Users/Desktop/12.jpg");
//	imshow("原图", img);
//
//
//	int bins = 256;
//	int hist_size[] = { bins };
//	float range[] = { 0,256 };
//	const float* ranges[] = { range };
//	MatND redhist, greenhist, bluehist;
//	int channels_r[] = { 0 };
//
//	calcHist(&img, 1, channels_r, Mat(),
//		redhist, 1, hist_size, ranges,
//		true, false);
//	int channels_g[] = { 1 };
//	calcHist(&img, 1, channels_g, Mat(),
//		greenhist, 1, hist_size, ranges,
//		true, false);
//	int channels_b[] = { 2 };
//	calcHist(&img, 1, channels_b, Mat(),
//		bluehist, 1, hist_size, ranges,
//		true,
//		false);
//
//
//	double maxvalue_red, maxvalue_green, maxvalue_blue;
//	minMaxIdx(redhist, 0, &maxvalue_red, 0, 0);
//	minMaxIdx(greenhist, 0, &maxvalue_green, 0, 0);
//	minMaxIdx(bluehist, 0, &maxvalue_blue, 0, 0);
//	int scale = 1;
//	int hisheight = 256;
//	Mat hisimage = Mat::zeros(hisheight, bins * 3, CV_8UC3);
//
//	for (int i = 1; i < bins; i++)
//	{
//
//		float binvalue_red = redhist.at<float>(i);
//		float binvalue_green = greenhist.at<float>(i);
//		float binvalue_blue = bluehist.at<float>(i);
//		int intensity_red =
//			cvRound(binvalue_red * hisheight / maxvalue_red);
//		int intensity_green =
//			cvRound(binvalue_green * hisheight / maxvalue_green);
//		int intensity_blue =
//			cvRound(binvalue_blue * hisheight / maxvalue_blue);
//
//		rectangle(hisimage, Point(i * scale, hisheight - 1), Point((i + 1) * scale - 1, hisheight - intensity_red), Scalar(255, 0, 0));
//
//		rectangle(hisimage, Point((i + bins) * scale, hisheight - 1), Point((i + bins + 1) * scale - 1, hisheight - intensity_green), Scalar(0, 255, 0));
//
//		rectangle(hisimage, Point((i + bins * 2) * scale, hisheight - 1), Point((i + bins * 2 + 1) * scale - 1, hisheight - intensity_blue), Scalar(0, 0, 255));
//	}
//
//	imshow("图像的RGB直方图", hisimage);
//	waitKey(5);
//
//	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
//	Mat dstimage1;
//	Mat dstimage2;
//	erode(img, dstimage1, element);
//
//	blur(img, dstimage2, Size(7, 7));
//
//	Mat edge, grayimage;
//
//	cvtColor(img, grayimage, CV_BGR2GRAY);
//	blur(grayimage, edge, Size(3, 3));
//
//	Canny(edge, edge, 3, 9, 3);
//
//	imshow("原图", img);
//
//	imshow("效果图-腐蚀操作", dstimage1);
//	imshow("效果图-模糊操作", dstimage2);
//	imshow("效果图-canny边缘监测操作", edge);
//
//	waitKey(60000);
//	return 0;
//}