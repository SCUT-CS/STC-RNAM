#pragma once
#include "Headers.h"

/** Calculators
  * @author CuiYuxin */
class Calculate
{
public:
	static double PSNR(Mat img1, Mat imggest);
	static double BPP(vector<colorListStandard>& P, Size imgSize, vector<char>& Q);
	
};

