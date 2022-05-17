#pragma once
#include <QThread>

class AlgoThread : public QThread
{
	Q_OBJECT

signals:
    //sent STC results
    void sentSTCRes(Tuple res);
    //sent RANM results
    void sentDPRes(Tuple res);
public:
	AlgoThread(QObject *parent);
	~AlgoThread();
    void run()override;
};
