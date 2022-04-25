#pragma once
#include <iostream>
#include <vector>
#include "opencv.hpp"
using namespace std;
using namespace cv;
extern int reg_num;
extern int bitnum;
extern int cur_block;
extern double thresU;
extern double thresVar;
struct doubleCoordinate;
struct colorListStandard;
extern vector<doubleCoordinate> C; //建立坐标表
extern vector<colorListStandard> P; //建立颜色表

/** Standard Color List
  * @author CuiYuxin */
struct colorListStandard //标准矩形颜色表
{
	uchar g1, g2, g3, g4;
    void setFirstHalf(uchar c1, uchar c2);
    void setLastHalf(uchar c3, uchar c4);
};

/** up left corner and down right corner coordinate
  * @author CuiYuxin */
struct doubleCoordinate //左上角及右下角坐标
{
	pair<int, int> dot1;
	pair<int, int> dot2;
    doubleCoordinate(){};
    doubleCoordinate(int x1, int y1, int x2, int y2);
    void setCoordinate(int x1, int y1,int x2,int y2);
};

/** Segment int Params
  * @author CuiYuxin */
struct SegmentParamI //左上角及右下角坐标
{
    SegmentParamI(int x,int y,int l,int h);
    int xLeft;
    int yupper;
    int len;
    int width;
};

/** Inline Functions
  * @author ZhengYunping */
inline double Gst(int g2, int g1, int w)
{
    return (g2 - g1) / (w - 1.0);
}
inline double Gsb(int g4, int g3, int w)
{
    return (g4 - g3) / (w - 1.0);
}
inline double Gsl(int g3, int g1, int h)
{
    return (g3 - g1) / (h - 1.0);
}
inline double Gsr(int g4, int g2, int h)
{
    return (g4 - g2) / (h - 1.0);
}
inline double C1(int w)
{
    return (2 * w - 1) / (6 * (w - 1.0));
}
inline double C2(int h)
{
    return (2 * h - 1) / (6 * (h - 1.0));
}
inline double D1(int g1, int g2, int g3, int g4, int w, int h)
{
    return (g4 - g3 - g2 + g1) / ((w - 1.0) * (h - 1));
}
inline double Uc(int na, int nb, double ua, double ub)
{
    return (na * ua + nb * ub) / (na + nb);
}
inline double Varc(int na, int nb, double vara, double varb, double ua, double ub)
{
    return (na * vara + nb * varb) / (na + nb) + (na * nb * (ua - ub) * (ua - ub)) / ((na + nb) * (na + nb));
}

/** Inline Functions
  * @author CuiYuxin */
inline double Ubi(colorListStandard color, doubleCoordinate coor)
{
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
inline double Squaresumbi(colorListStandard color, doubleCoordinate coor)
{
    int x1 = coor.dot1.first;
    int y1 = coor.dot1.second;
    int x2 = coor.dot2.first;
    int y2 = coor.dot2.second;
    int w = x2 - x1 + 1;
    int h = y2 - y1 + 1;
    double c1 = C1(w);
    double c2 = C2(h);
    if (x1 < x2 && y1 < y2)
        return w * h * ((0.5 - c1 - c2) * (color.g1 * color.g4 + color.g2 * color.g3) + c1 * (color.g2 * color.g4 + color.g1 * color.g3) + c2 * (color.g3 * color.g4 + color.g1 * color.g2) + c1 * c2 * (color.g4 - color.g3 - color.g2 + color.g1) * (color.g4 - color.g3 - color.g2 + color.g1));
    else if (x1 == x2 && y1 == y2)
        return w * h * color.g1 * color.g1;
    else if (y1 == y2)
        return w * h * (color.g1 * color.g2 + c1 * (color.g2 - color.g1) * (color.g2 - color.g1));
    else if (x1 == x2)
        return w * h * (color.g1 * color.g3 + c2 * (color.g3 - color.g1) * (color.g3 - color.g1));
}
inline double Varbi(colorListStandard color, doubleCoordinate coor)
{
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
        double ubi = Ubi(color, coor);
        return ((0.5 - c1 - c2) * (color.g1 * color.g4 + color.g2 * color.g3) + c1 * (color.g2 * color.g4 + color.g1 * color.g3) + c2 * (color.g3 * color.g4 + color.g1 * color.g2) + c1 * c2 * (color.g4 - color.g3 - color.g2 + color.g1) * (color.g4 - color.g3 - color.g2 + color.g1) - ubi * ubi);
    }
    else if (x1 == x2 && y1 == y2)
        return 0;
    else if (y1 == y2)
        return (c1 - 0.25) * (color.g2 - color.g1) * (color.g2 - color.g1);
    else if (x1 == x2)
        return (c2 - 0.25) * (color.g3 - color.g1) * (color.g3 - color.g1);
}
inline char getBit(vector<char>& Q)
{
    return Q[bitnum++];
}


