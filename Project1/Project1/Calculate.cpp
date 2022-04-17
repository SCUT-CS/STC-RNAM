#include "Calculate.h"

/** Calculate the PSNR
  * @author CuiYuxin
  * @param Mat img1
  * @param Mat imggest
  * @return double PSNR */
double Calculate::PSNR(Mat img1, Mat imggest)
{
	int M = img1.rows; //Í¼Ïñ¸ß¶È
	int N = img1.cols; //Í¼Ïñ¿í¶È
	double temp = 0;
	for (int y = 0; y < M; y++)
	{
		uchar* ptr1 = (uchar*)(img1.data + y * img1.step);
		uchar* ptrg = (uchar*)(img1.data + y * img1.step);
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
  * @param MatSize imgSize
  * @param vector<char>& Q
  * @return double BPP */
double Calculate::BPP(vector<colorListStandard>& P, Size imgSize, vector<char>& Q)
{
	return (Q.size() + 32.0 * P.size()) / (imgSize.height * imgSize.width);
}
