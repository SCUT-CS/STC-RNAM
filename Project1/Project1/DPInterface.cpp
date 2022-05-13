#include "DPInterface.h"
#include "Calculate.h"

/** STC algorithm
  * @author CuiYuxin
  * @param String fileDir
  * @param String imgDir
  * @param int margin
  * @param int ratio
  * @return if success */
bool DPAlgo::DP(String fileDir, String imgDir, double margin, double ratio)
{
	Mat img;
	img = imread(fileDir, 0); //将源彩色图像img转化成目标灰色图像读入
	if (!img.empty())
	{
		//保存图片
		imwrite(imgDir + "原始灰度图像.bmp", img);
		/*一，分割同类块及编码*/
		Size size = img.size();
		int height = size.height;
		int width = size.width;
		Mat markMatrix = Mat::zeros(size, img.type());
		Mat R = Mat::zeros(size, img.type());
		int num = 0;
		vector<ColorNode> colorList;
		vector<DoubleDots> locList;
		time_t begin, end;
		begin = clock();
		/*分块*/
		Algo::StartNamCut(img, markMatrix, R, colorList, locList, size, margin, num, ratio);
		/*矩阵编码*/
		vector<char> Q;
		Algo::EnCode(R, size, Q);
		end = clock();
		encodeTime = end - begin;
		/*二，还原图像矩阵及图像*/
		Mat T = Mat::zeros(img.size(), img.type());
		begin = clock();
		Algo::Decode(T, size, Q);
		Mat newImg = Mat::zeros(img.size(), img.type());
		Algo::RestoreImage(newImg, markMatrix, T, colorList, size);
		end = clock();
		decodeTime = end - begin;
		blockNum = num;
		psnr = PSNR(img, newImg);
		bpp = Calculate::BPP(colorList, width, height, Q);
		cr = 8.0 / bpp;
		//保存图片
		imwrite(imgDir + "压缩图灰度图像newImg.bmp", newImg);
		//imwrite(imgDir + "压缩图灰度图像img.bmp", img);
		/*三，画分割图*/
		Mat sketch;
		int xr, yr;
		int sketchXn, sketchYn;
		if (height >= 256 || width >= 256)
		{
			xr = 1, yr = 1, sketchXn = height, sketchYn = width;
			sketch = Mat::zeros(img.size(), img.type());
		}
		else
		{
			xr = 511 / (height - 1);
			yr = 511 / (width - 1);
			sketchXn = 512, sketchYn = 512;
			sketch = Mat::zeros(Size(512, 512), img.type());
		}
		for (int i = 0; i < sketchYn; i++)
		{
			uchar* ptrsketch = (uchar*)(sketch.data + i * sketch.step);
			for (int j = 0; j < sketchXn; j++)
			{
				ptrsketch[j] = 255;
			}
		}
		for (int i = 0; i < locList.size(); i++)
		{
			if (locList[i].dot1.first == 0 && locList[i].dot1.second == 0)
				rectangle(sketch, Point(locList[i].dot1.first, locList[i].dot1.second), Point(locList[i].dot2.first, locList[i].dot2.second), Scalar(0x00, 0x00, 0x00));
			else   if (locList[i].dot1.first == 0 && locList[i].dot1.second != 0)
				rectangle(sketch, Point(locList[i].dot1.first, locList[i].dot1.second - 1), Point(locList[i].dot2.first, locList[i].dot2.second), Scalar(0x00, 0x00, 0x00));
			else   if (locList[i].dot1.first != 0 && locList[i].dot1.second == 0)
				rectangle(sketch, Point(locList[i].dot1.first - 1, locList[i].dot1.second), Point(locList[i].dot2.first, locList[i].dot2.second), Scalar(0x00, 0x00, 0x00));
			else   if (locList[i].dot1.first != 0 && locList[i].dot1.second != 0)
				rectangle(sketch, Point(locList[i].dot1.first - 1, locList[i].dot1.second - 1), Point(locList[i].dot2.first, locList[i].dot2.second), Scalar(0x00, 0x00, 0x00));
		}
		//保存图片
		imwrite(imgDir + "分割示意图.bmp", sketch);
	}
	return false;
}
