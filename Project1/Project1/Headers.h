#pragma once
#include "opencv.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;

struct colorListStandard //标准矩形颜色表
{
	uchar g1, g2, g3, g4;
};

struct doubleCoordinate //左上角及右下角坐标
{
	pair<int, int> dot1;
	pair<int, int> dot2;
};

