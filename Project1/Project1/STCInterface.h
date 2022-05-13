#pragma once
#include "Headers.h"
#include "Tree.h"
#include "Algo.h"
#include "Calculate.h"
#include "Segment.h"
#include "Region.h"
class STCAlgo
{
public:
    STCAlgo() {}
    STCAlgo(String fDir, String iDir, double m, double r, double v, int c) :fileDir(fDir), imgDir(iDir), margin(m), ratio(r), variance(v), cutMethod(c) {}
    bool STC(String fileDir, String imgDir, double margin, double ratio, double variance, int cutMethod);
    bool STC()
    {
        return STC(fileDir, imgDir, margin, ratio, variance, cutMethod);
    }

    //输入信息
    //1.原彩图 要被读入的文件路径
    String fileDir;
    //2.newimg保存路径
    String imgDir;
    //3.同类快阀值 margin的值
    double margin;
    //4.均值阀值 ratio的值
    double ratio;
    //5.方差阀值
    double variance;
    //6.切法 1 水平 0垂直
    int cutMethod;

    //输出信息+代码中保存图像部分
    //编码所用时间
    time_t codeTime;
    //解码所用时间
    //time_t decodeTime;
    //块数
    int blockNum;
    //BPP
    double bpp;
    //CR
    double cr;
    //Converage time of QSC
    time_t cverTime;
    //2*2块数量
    int blockNum_2;
    //PSNR
    double psnr;
    //区域数量
    int areaNum;
};

