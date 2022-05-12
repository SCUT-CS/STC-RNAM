#pragma once
#include "Headers.h"
class Varialbes
{
public:
	int reg_num = 0;
	int bitnum = 0;
	double thresU = 0;
	double thresVar = 0;
	int cur_block = -1;
	vector<DoubleDots> C; //建立坐标表
	vector<colorListStandard> P; //建立颜色表
	vector<char> Q; //建立线性树表
	/** Inline functions
      * @author CuiYuxin */
	inline char getBit(vector<char>& Q)
	{
		return Q[bitnum++];
	}
	inline double Ubi()
	{
		colorListStandard color = P[cur_block];
		DoubleDots coor = C[cur_block];
		int x1 = coor.dot1.first;
		int y1 = coor.dot1.second;
		int x2 = coor.dot2.first;
		int y2 = coor.dot2.second;
		if (x1 < x2 && y1 < y2)
			return (color.g1 + color.g2 + color.g3 + color.g4) / 4.0;
		else if (x1 == x2 && y1 == y2)
			return color.g1;
		else if (y1 == y2)
			return (color.g1 + color.g2) / 2.0;
		else if (x1 == x2)
			return (color.g1 + color.g3) / 2.0;
	}
	inline double Varbi()
	{
		colorListStandard color = P[cur_block];
		DoubleDots coor = C[cur_block];
		int x1 = coor.dot1.first;
		int y1 = coor.dot1.second;
		int x2 = coor.dot2.first;
		int y2 = coor.dot2.second;
		int w = x2 - x1 + 1;
		int h = y2 - y1 + 1;
		double c1 = C1(w);
		double c2 = C2(h);
		if (x1 < x2 && y1 < y2)
		{
			double ubi = Ubi();
			return ((0.5 - c1 - c2) * (color.g1 * color.g4 + color.g2 * color.g3) + c1 * (color.g2 * color.g4 + color.g1 * color.g3) + c2 * (color.g3 * color.g4 + color.g1 * color.g2) + c1 * c2 * (color.g4 - color.g3 - color.g2 + color.g1) * (color.g4 - color.g3 - color.g2 + color.g1) - ubi * ubi);
		}
		else if (x1 == x2 && y1 == y2)
			return 0;
		else if (y1 == y2)
			return (c1 - 0.25) * (color.g2 - color.g1) * (color.g2 - color.g1);
		else if (x1 == x2)
			return (c2 - 0.25) * (color.g3 - color.g1) * (color.g3 - color.g1);
	}
};
