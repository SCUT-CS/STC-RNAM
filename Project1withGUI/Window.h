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
#include "ui_Window.h"

class Window : public QMainWindow
{
    Q_OBJECT

signals:

public slots:
    void openFile();
    void saveFile();
    void about();

public:
    Window(QWidget* parent = Q_NULLPTR);

private:
    friend class AlgoThread;
    Ui::WindowClass ui;
    //输入信息
    QString fileDir;
    double margin;
    double ratio;
    double variance;
    int cutMethod;
    void openImg(QString fileName);
};
