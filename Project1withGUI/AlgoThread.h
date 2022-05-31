#pragma once
#include <QThread>
#include <cassert>
#include "../Project1/Project1/STCInterface.h"
#include "Window.h"
#include "../Project1/Project1/DPInterface.h"

class AlgoThread : public QThread
{
    Q_OBJECT

signals:
    //sent STC results
    void sentSTCRes(time_t codeTime, int blockNum, double bpp, double cr, time_t cverTime, int blockNum_2, double psnr, int areaNum);
    //sent RANM results
    void sentDPRes(time_t encodeTime, time_t decodeTime, int blockNum, double psnr, double bpp, double cr);
    //show the results

public:
    AlgoThread(QObject* parent);
    ~AlgoThread();
    void run()override;
    // 输入信息
    QString fileDir;
    double margin;
    double ratio;
    double variance;
    int cutMethod;
};
