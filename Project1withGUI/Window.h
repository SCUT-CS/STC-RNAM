#pragma once

#include <QtWidgets/QMainWindow>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QScreen>
#include <QLabel>
#include <QSize>
#include <QGraphicsScene>
#include "AlgoThread.h"
#include "ui_Window.h"

class Window : public QMainWindow
{
    Q_OBJECT

signals:

public slots:
    void openFile();
    void saveFile();
    void about();
    void setMargin(double m);
    void setRatio(double r);
    void setVariance(double v);
    void setCutMethod(QString c);
    void startRun();
    void showSTC(time_t codeTime, int blockNum, double bpp, double cr, time_t cverTime, int blockNum_2, double psnr, int areaNum);
    void showRNAM(time_t encodeTime, time_t decodeTime, int blockNum, double psnr, double bpp, double cr);

public:
    Window(QWidget* parent = Q_NULLPTR);

private:
    friend class AlgoThread;
    Ui::WindowClass ui;

    AlgoThread *algo;

    //输入信息
    QString fileDir;
    double margin = 30;
    double ratio = 10;
    double variance = 225;
    int cutMethod = 0;

    QImage* openImg(QString fileName);

};
