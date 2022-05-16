#pragma once
#include "Headers.h"
#include "Algo.h"

class DPAlgo
{
public:
	DPAlgo() {}
	DPAlgo(String fDir, String iDir, double m, double r) :fileDir(fDir), imgDir(iDir), margin(m), ratio(r) {}
	bool DP(String fileDir, String imgDir, double margin, double ratio);
	bool DP()
	{
		return DP(fileDir, imgDir, margin, ratio);
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

	//输出信息
	//编码所用时间
	time_t encodeTime;
	//解码所用时间
	time_t decodeTime;
	//块数
	int blockNum;
	//PSNR
	double psnr;
	//BPP
	double bpp;
	//CR
	double cr;
};

