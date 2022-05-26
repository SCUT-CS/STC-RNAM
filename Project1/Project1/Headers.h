#pragma once
#include <iostream>
#include <vector>
#include "opencv.hpp"
using namespace std;
using namespace cv;
struct DoubleDots;
struct colorListStandard;

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
struct DoubleDots //左上角及右下角坐标
{
    pair<int, int> dot1;
    pair<int, int> dot2;
    DoubleDots() {};
    DoubleDots(int x1, int y1, int x2, int y2);
    void setCoordinate(int x1, int y1, int x2, int y2);
};

/** Segment int Params
  * @author CuiYuxin */
struct SegmentParamI 
{
    SegmentParamI(int x, int y, int l, int h);
    int xLeft;
    int yupper;
    int len;
    int width;
};

/** Color Node
  * @author CuiYuxin */
struct ColorNode
{
    //0普通矩阵，1宽为1矩阵，2长为1矩阵，3孤立点
    int kind, g1, g2, g3, g4;
    ColorNode(int k, int gg1, int gg2 = -1, int gg3 = -1, int gg4 = -1) :kind(k), g1(gg1), g2(gg2), g3(gg3), g4(gg4) {};
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
inline double Squaresumbi(colorListStandard color, DoubleDots coor)
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