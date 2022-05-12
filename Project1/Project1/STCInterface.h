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
    bool STC(String fileDir, String imgDir, int margin, int ratio, int variance, int cutMethod);

    //输入信息
    //1.原彩图 要被读入的文件的文件名
    String fileDir;
    //2.转换灰度图文件名 img保存路径
    String grayDir;
    //3.转换RNAMC文件名 newimg保存路径
    String imgDir;
    //4.同类快阀值 margin的值
    int margin;
    //5.均值阀值 ratio的值
    int ratio;
    //6.方差阀值
    int variance;
    //7.切法 1 水平 0垂直
    int cutMethod;
	
	//输出信息+代码中保存图像部分
	//编码所用时间
    time_t codeTime;
    //解码所用时间
    //time_t decodeTime;
	//块数
    int blockNum;
	//BPP
    int bpp;
	//CR
    int cr;
	//Converage time of QSC
    time_t cverTime;
	//2*2块数量
    int blockNum_2;
	//PSNR
    double psnr;
	//区域数量
    int areaNum;
};

