#pragma once
#include "Headers.h"

/** Calculators and other utilities
  * @author CuiYuxin */
class Calculate
{
public:
	static double BPP(vector<colorListStandard>& P, Size imgSize, vector<char>& Q);
	static double BPP(vector<ColorNode>& cn, int xn, int yn, vector<char>& Q);
};

