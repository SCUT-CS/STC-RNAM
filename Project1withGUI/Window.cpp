#include "Window.h"

/** Main window.
  * @author CuiYuxin YangYaocheng */
Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QLabel* statusLabel = new QLabel;
    statusLabel->setText("V1.00");
    ui.statusBar->addWidget(statusLabel);
    algo = new AlgoThread(this);
    algo->p = this;
    // 创建文件夹 "./RNAM" "./STC"
    QDir RNAMDir("/RNAM");
    QDir STCDir("/STC");
    if(!RNAMDir.exists())
    {
        RNAMDir.mkdir("/RNAM");
    }
    if (!STCDir.exists())
    {
        STCDir.mkdir("/STC");
    }
    connect(ui.openFile, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui.saveFile, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui.openFile2, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(ui.about, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui.margin, SIGNAL(valueChanged(double)), this,SLOT(setMargin(double)));
    connect(ui.ratio, SIGNAL(valueChanged(double)), this, SLOT(setRatio(double)));
    connect(ui.variance, SIGNAL(valueChanged(double)), this, SLOT(setVariance(double)));
    connect(ui.cutMethod, SIGNAL(currentTextChanged(QString)), this, SLOT(setCutMethod(QString)));
    connect(algo, SIGNAL(sentSTCRes(time_t, int, double, double, time_t, int, double, int)), this, SLOT(showSTC(time_t, int, double, double, time_t, int, double, int)));
    connect(algo, SIGNAL(sentDPRes(time_t, time_t, int, double, double, double)), this, SLOT(showRNAM(time_t, time_t, int, double, double, double)));

    connect(ui.start, SIGNAL(clicked()), this, SLOT(startRun()));
}

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
    ui.STC->setPixmap(QPixmap::fromImage(*openImg("/STC/original.bmp")));
    ui.STC_2->setPixmap(QPixmap::fromImage(*openImg("/STC/2split.bmp")));
    ui.STC_3->setPixmap(QPixmap::fromImage(*openImg("/STC/region1.bmp")));
    ui.STC_4->setPixmap(QPixmap::fromImage(*openImg("/STC/region2.bmp")));
}

void Window::showRNAM(time_t encodeTime, time_t decodeTime, int blockNum, double psnr, double bpp, double cr)
{
    ui.encodeTime->setText(QString::number(encodeTime));
    ui.decodeTime->setText(QString::number(decodeTime));
    ui.blockNum_2->setText(QString::number(blockNum));
    ui.psnr_2->setText(QString::number(psnr));
    ui.bpp_2->setText(QString::number(bpp));
    ui.cr_2->setText(QString::number(cr));
    ui.RNAM->setPixmap(QPixmap::fromImage(*openImg("/RNAM/zipImg.bmp")));
    ui.RNAM_2->setPixmap(QPixmap::fromImage(*openImg("/RNAM/original.bmp")));
    ui.RNAM_3->setPixmap(QPixmap::fromImage(*openImg("/RNAM/split.bmp")));
}

void Window::startRun()
{
    algo->fileDir= this->fileDir;
    algo->margin =this->margin;
    algo->ratio = this->ratio;
    algo->variance =this->variance;
    algo->cutMethod = this->cutMethod;
    algo->start();
}

/** Set the margin
  * @author YangYaocheng */
void Window::setMargin(double m)
{
    this->margin = m;
}

/** Set the ratio
  * @author YangYaocheng */
void Window::setRatio(double r)
{
    this->ratio = r;
}

/** Set the variance
  * @author YangYaocheng */
void Window::setVariance(double v)
{
    this->variance=v;
}

/** Set the cutMethod
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

/** Save a image file.
  * @author CuiYuxin YangYaocheng */
void Window::saveFile()
{
    //QString filename1 = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Images (*.png *.bmp *.jpg)")); //选择路径
    //QScreen* screen = QGuiApplication::primaryScreen();
    //screen->grabWindow(ui.labelname.winId()).save(filename1);
}

/** Open an about Window.
  * @author CuiYuxin YangYaocheng */
void Window::about()
{
    QString content = "// TODO";
    QMessageBox aboutWindow(QMessageBox::NoIcon, QString("关于"), content);
    //aboutWindow.setIconPixmap("xxxxxxxxxxxxxxxxxxxxxxx.png");
    aboutWindow.exec();
}


