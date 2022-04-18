#pragma once
#include "Headers.h"
#include "Tree.h"
/** Implement the algotirhm
  * @author CuiYuxin */
class Algo
{
public:
	static bool JudgeSameBlock(double epsilon, Mat img, doubleCoordinate dots);
	static void BuildTree(Mat img, treeIterator it, vector<colorListStandard>& P, vector<doubleCoordinate>& C, int& num, double epsilon, doubleCoordinate dots);//分割原图.建立矩阵R.颜色表P
};

