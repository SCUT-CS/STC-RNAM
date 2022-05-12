#pragma once
#include "Headers.h"
#include "Tree.h"
/** Implement the algotirhm
  * @author CuiYuxin */
class Algo
{
public:
	//STC
	static bool JudgeSameBlock(double epsilon, Mat img, DoubleDots dots);
	static void BuildTree(Mat img, treeIterator it, vector<colorListStandard>& P, vector<DoubleDots>& C, int& num, double epsilon, DoubleDots dots); //分割原图.建立矩阵R.颜色表P
	static void MakeImggest(Mat imggest, vector<colorListStandard>& P, vector<DoubleDots> C); //建立gest图像
	//DP
	static void EnCode(Mat R, Size s, vector<char>& Q);
	static void Decode(Mat R, Size s, const vector<char>& Q);
	static bool IsSameBlock(const Mat img, DoubleDots dots, int margin);
	static DoubleDots FindSameBlock(const Mat img, Mat markMatrix, Mat R, int x1, int y1, double margin, double ratio);
	static void RestoreImage(Mat img, Mat markMatrix, Mat R, vector<ColorNode> cn, Size s);
	void RestoreImageValue(Mat img, ColorNode node, DoubleDots dots);
	void SetMarkMatrix(Mat markMatrix, DoubleDots dots, int value);
	void StartNamCut(const Mat img, Mat markMatrix, Mat R, vector<ColorNode>& ColorList, vector<DoubleDots>& LocList, Size size, double margin, int& num, double ratio);
};

