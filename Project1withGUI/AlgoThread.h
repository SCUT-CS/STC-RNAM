#pragma once
#include <QThread>

class AlgoThread : public QThread
{
	Q_OBJECT

signals:
    //sent STC results
    void sentSTCRes(); // TODO 添加参数
    //sent RANM results
    void sentDPRes(); // TODO 添加参数
public:
	AlgoThread(QObject *parent);
	~AlgoThread();
    void run()override;
};
