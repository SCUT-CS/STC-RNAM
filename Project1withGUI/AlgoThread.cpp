#include "AlgoThread.h"

AlgoThread::AlgoThread(QObject* parent)
	: QThread(parent)
{
}

AlgoThread::~AlgoThread()
{
}

/** Emit STC & BP in a new thread
  * @author YangYaocheng */
void AlgoThread::run()
{
	assert(this->parent() != nullptr); //断言父类指针非空
	STCAlgo stc;
	Window* p = (Window*)this->parent();
	stc.STC(p->fileDir.toStdString(), p->margin, p->ratio, p->variance, p->cutMethod);
	emit sentSTCRes(stc.codeTime, stc.blockNum, stc.bpp, stc.cr, stc.cverTime, stc.blockNum_2, stc.psnr, stc.areaNum);
	DPAlgo dp;
	dp.DP(p->fileDir.toStdString(), p->margin, p->ratio);
	emit sentDPRes(dp.encodeTime, dp.decodeTime, dp.blockNum, dp.psnr, dp.bpp, dp.cr);
}
