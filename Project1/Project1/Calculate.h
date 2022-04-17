#pragma once
#include "Headers.h"

/** Calculators and other utilities
  * @author CuiYuxin */
class Calculate
{
public:
	static double PSNR(Mat img, Mat imggest);
	static double BPP(vector<colorListStandard>& P, Size imgSize, vector<char>& Q);
	static bool JudgeSameBlock(double epsilon,Mat img, doubleCoordinate dots);
};

