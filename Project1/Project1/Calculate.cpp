#include "Calculate.h"

/** Calculate the PSNR
  * @author CuiYuxin
  * @param Mat img1
  * @param Mat imggest
  * @return double PSNR */
double Calculate::PSNR(Mat img, Mat imggest)
{
	int M = img.rows; //Í¼Ïñ¸ß¶È
	int N = img.cols; //Í¼Ïñ¿í¶È
	double temp = 0;
	for (int y = 0; y < M; y++)
	{
		uchar* ptr1 = (uchar*)(img.data + y * img.step);
		uchar* ptrg = (uchar*)(img.data + y * img.step);
		for (int x = 0; x < N; x++)
		{
			temp += pow((double)(ptr1[x] - ptrg[x]), 2);
		}
	}
	double temp1 = 0;
	temp1 = 10 * log10(255.0 * 255 * M * N / temp);
	return (temp1);
}

/** Calculate the BPP
  * @author CuiYuxin
  * @param vector<colorListStandard>& P
  * @param Size imgSize
  * @param vector<char>& Q
  * @return double BPP */
double Calculate::BPP(vector<colorListStandard>& P, Size imgSize, vector<char>& Q)
{
	return (Q.size() + 32.0 * P.size()) / (imgSize.height * imgSize.width);
}

/** Judge if blocks are the same
  * @author CuiYuxin
  * @param double epsilon
  * @param Mat img
  * @param doubleCoordinate dots
  * @return bool isSame */
bool Calculate::JudgeSameBlock(double epsilon, Mat img, doubleCoordinate dots)
{
	int x1 = dots.dot1.first;
	int y1 = dots.dot1.second;
	int x2 = dots.dot2.first;
	int y2 = dots.dot2.second;
	uchar* ptrtemp = (uchar*)(img.data + y1 * img.step);
	uchar g1 = ptrtemp[x1];
	uchar g2 = ptrtemp[x2];
	ptrtemp = (uchar*)(img.data + y2 * img.step);
	uchar g3 = ptrtemp[x1]; 
	uchar g4 = ptrtemp[x2];
	for (int y = y1; y <= y2; y++)
	{
		uchar* ptr = (uchar*)(img.data + y * img.step);
		for (int x = x1; x <= x2; x++)
		{
			uchar g = ptr[x];
			double i1 = (double)(y - y1) / (y2 - y1);
			double i2 = (double)(x - x1) / (x2 - x1);
			double g5 = g1 + (g2 - g1) * i2;
			double g6 = g3 + (g4 - g3) * i2;
			double gest = g5 + (g6 - g5) * i1;
			if (g - gest >= -epsilon && g - gest <= epsilon)
			{
				continue;
			}
			else 
			{
				return false; 
			}
		}
	}
	return true;	
}

