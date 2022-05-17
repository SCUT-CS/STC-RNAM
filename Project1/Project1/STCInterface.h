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
    STCAlgo(String fDir, double m, double r, double v, int c) :fileDir(fDir),margin(m), ratio(r), variance(v), cutMethod(c) {}
    bool STC(String fileDir, double margin, double ratio, double variance, int cutMethod);
    bool STC()
    {
        return STC(fileDir,margin, ratio, variance, cutMethod);
    }

    //输入信息
    //1.原彩图 要被读入的文件路径
    String fileDir;
    //2.同类快阀值 margin的值
    double margin;
    //3.均值阀值 ratio的值
    double ratio;
    //4.方差阀值
    double variance;
    //5.切法 1 水平 0垂直
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

