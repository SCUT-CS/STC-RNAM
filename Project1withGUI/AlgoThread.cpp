#include "AlgoThread.h"

AlgoThread::AlgoThread(QObject* parent)
	: QThread(parent)
{
}

AlgoThread::~AlgoThread()
{
}

/** Run STC & RNAM algorithm in a new thread
  * @author YangYaocheng ZhouTongyv  */
void AlgoThread::run()
{
	STCAlgo stc;
	stc.STC(fileDir.toStdString(),margin, ratio, variance, cutMethod);
	emit sentSTCRes(stc.codeTime, stc.blockNum, stc.bpp, stc.cr, stc.cverTime, stc.blockNum_2, stc.psnr, stc.areaNum);
	DPAlgo dp;
	dp.DP(fileDir.toStdString(), margin, ratio);
	emit sentDPRes(dp.encodeTime, dp.decodeTime, dp.blockNum, dp.psnr, dp.bpp, dp.cr);
}
