#include "Window.h"

/** Main window.
  * @author CuiYuxin YangYaocheng */
Window::Window(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QLabel* statusLabel = new QLabel;
    statusLabel->setText("Version 1.0.1 MIT License ©SCUT-CS/team-11 https://github.com/SCUT-CS/Project-1/");
    ui.statusBar->addWidget(statusLabel);
    algo = new AlgoThread(this);
    setWindowIcon(QPixmap::fromImage(*openImg(":/Project1/icon.jpg")));
    QDir RNAMDir("/RNAM");
    QDir STCDir("/STC");
    if (!RNAMDir.exists())
    {
        RNAMDir.mkdir("/RNAM");
    }
    if (!STCDir.exists())
    {
        STCDir.mkdir("/STC");
    }
    connect(ui.openFile, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui.saveSTC, SIGNAL(triggered()), this, SLOT(saveSTC()));
    connect(ui.saveRNAM, SIGNAL(triggered()), this, SLOT(saveRNAM()));
    connect(ui.openFile2, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(ui.about, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui.margin, SIGNAL(valueChanged(double)), this, SLOT(setMargin(double)));
    connect(ui.ratio, SIGNAL(valueChanged(double)), this, SLOT(setRatio(double)));
    connect(ui.variance, SIGNAL(valueChanged(double)), this, SLOT(setVariance(double)));
    connect(ui.cutMethod, SIGNAL(currentTextChanged(QString)), this, SLOT(setCutMethod(QString)));
    connect(algo, SIGNAL(sentSTCRes(time_t, int, double, double, time_t, int, double, int)), this, SLOT(showSTC(time_t, int, double, double, time_t, int, double, int)));
    connect(algo, SIGNAL(sentDPRes(time_t, time_t, int, double, double, double)), this, SLOT(showRNAM(time_t, time_t, int, double, double, double)));
    connect(ui.start, SIGNAL(clicked()), this, SLOT(startRun()));
}

/** Show STC tab
  * @param time_t codeTime
  * @param int blockNum
  * @param double bpp
  * @param double cr
  * @param time_t cverTime
  * @param int blockNum
  * @param int blockNum_2
  * @param double psnr
  * @param int areaNum
  * @author ZhouTongyv YangYaocheng */
void Window::showSTC(time_t codeTime, int blockNum, double bpp, double cr, time_t cverTime, int blockNum_2, double psnr, int areaNum)
{
    ui.codeTime->setText(QString::number(codeTime));
    ui.blockNum->setText(QString::number(blockNum));
    ui.bpp->setText(QString::number(bpp));
    ui.cr->setText(QString::number(cr));
    ui.cverTime->setText(QString::number(cverTime));
    ui.blockNum_2->setText(QString::number(blockNum_2));
    ui.psnr->setText(QString::number(psnr));
    ui.areaNum->setText(QString::number(areaNum));
    QSize picSize(600, 400);
    QPixmap::fromImage(*openImg("/STC/original.bmp")).scaled(picSize, Qt::KeepAspectRatio);
    QGraphicsScene* STC = new  QGraphicsScene;
    QGraphicsScene* STC_2 = new  QGraphicsScene;
    QGraphicsScene* STC_3 = new  QGraphicsScene;
    QGraphicsScene* STC_4 = new  QGraphicsScene;
    STC->addPixmap(QPixmap::fromImage(*openImg("/STC/original.bmp")));
    STC_2->addPixmap(QPixmap::fromImage(*openImg("/STC/2split.bmp")));
    STC_3->addPixmap(QPixmap::fromImage(*openImg("/STC/region1.bmp")));
    STC_4->addPixmap(QPixmap::fromImage(*openImg("/STC/region2.bmp")));
    ui.STC->setScene(STC);
    ui.STC_2->setScene(STC_2);
    ui.STC_3->setScene(STC_3);
    ui.STC_4->setScene(STC_4);
    ui.STC->show();
    ui.STC_2->show();
    ui.STC_3->show();
    ui.STC_4->show();
}

/** Show RNAM tab
  * @param time_t encodeTime
  * @param time_t decodeTime
  * @param int blockNum
  * @param double psnr
  * @param double bpp
  * @param double cr
  * @author ZhouTongyv YangYaocheng */
void Window::showRNAM(time_t encodeTime, time_t decodeTime, int blockNum, double psnr, double bpp, double cr)
{
    ui.encodeTime->setText(QString::number(encodeTime));
    ui.decodeTime->setText(QString::number(decodeTime));
    ui.blockNum_2->setText(QString::number(blockNum));
    ui.psnr_2->setText(QString::number(psnr));
    ui.bpp_2->setText(QString::number(bpp));
    ui.cr_2->setText(QString::number(cr));
    QGraphicsScene* RNAM = new  QGraphicsScene;
    QGraphicsScene* RNAM_2 = new  QGraphicsScene;
    QGraphicsScene* RNAM_3 = new  QGraphicsScene;
    RNAM->addPixmap(QPixmap::fromImage(*openImg("/RNAM/split.bmp")));
    RNAM_2->addPixmap(QPixmap::fromImage(*openImg("/RNAM/original.bmp")));
    RNAM_3->addPixmap(QPixmap::fromImage(*openImg("/RNAM/zipImg.bmp")));
    ui.RNAM->setScene(RNAM);
    ui.RNAM_2->setScene(RNAM_2);
    ui.RNAM_3->setScene(RNAM_3);
    ui.RNAM->show();
    ui.RNAM_2->show();
    ui.RNAM_3->show();
}

/** Run STC & RNAM algorithm in a new thread
  * @author YangYaocheng ZhouTongyv  */
void Window::startRun()
{
    algo->fileDir = this->fileDir;
    algo->margin = this->margin;
    algo->ratio = this->ratio;
    algo->variance = this->variance;
    algo->cutMethod = this->cutMethod;
    algo->start();
}

/** Set the margin
  * @param double m
  * @author YangYaocheng */
void Window::setMargin(double m)
{
    this->margin = m;
}

/** Set the ratio
  * @param double r
  * @author YangYaocheng */
void Window::setRatio(double r)
{
    this->ratio = r;
}

/** Set the variance
  * @param double v
  * @author YangYaocheng */
void Window::setVariance(double v)
{
    this->variance = v;
}

/** Set the cutMethod
  * @param QString c
  * @author YangYaocheng */
void Window::setCutMethod(QString c)
{
    this->cutMethod = (c == "水平" ? 1 : 0);
}

/** Open a image file.
  * @author CuiYuxin YangYaocheng */
void Window::openFile()
{
    fileDir = QFileDialog::getOpenFileName(this, QString("打开图片"), QDir::homePath(), QString("Images (*.jpg *.bmp *.png *.jpeg *.gif)"));
}

/** Open a image file.
  * @param QString fileName
  * @author YangYaocheng */
QImage* Window::openImg(QString fileName)
{
    if (fileName.isEmpty())
    {
        return nullptr;
    }
    else
    {
        QImage* img = new QImage;
        if (!(img->load(fileName))) //加载图像
        {
            QMessageBox::information(this,
                tr("打开图像失败"),
                tr("打开图像失败!"));
            delete img;
            return nullptr;
        }
        return img;
    }
}

/** Save STC image file.
  * @author YangYaocheng */
void Window::saveSTC()
{
    QString file_path = QFileDialog::getSaveFileName(this, "请选择保存路径和文件名...", QDir::homePath());
    QPixmap::fromImage(*openImg("/STC/region1.bmp")).save(file_path);
}

/** Save RNAM image file.
  * @author YangYaocheng */
void Window::saveRNAM()
{
    QString file_path = QFileDialog::getSaveFileName(this, "请选择保存路径和文件名...", QDir::homePath());
    QPixmap::fromImage(*openImg("/RNAM/zipImg.bmp")).save(file_path);
}

/** Open an about Window.
  * @author CuiYuxin YangYaocheng */
void Window::about()
{
    QString content = "灰度图像表示STC和RNAM算法。\n作者：崔钰薪、杨曜诚、周通宇、罗智豪\n本程序遵循MIT开源协议，项目地址：https://github.com/SCUT-CS/Project-1";
    QMessageBox aboutWindow(QMessageBox::NoIcon, QString("关于本程序"), content);
    aboutWindow.setIcon(QMessageBox::Icon::Information);
    aboutWindow.exec();
}


