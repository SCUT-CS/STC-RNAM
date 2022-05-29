#include "Window.h"

/** Main window.
  * @author CuiYuxin YangYaocheng */
Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QLabel* statusLabel = new QLabel;
    statusLabel->setText("Version 1.0.1 MIT License ©SCUT-CS/team-11 https://github.com/SCUT-CS/Project-1/");
    ui.statusBar->addWidget(statusLabel);
    // TODO 创建文件夹 "./RNAM/" "./STC/"
    connect(ui.openFile, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui.saveFile, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui.openFile2, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(ui.about, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui.margin, SIGNAL(valueChanged(double)), this,SLOT(setMargin(double)));
    connect(ui.ratio, SIGNAL(valueChanged(double)), this, SLOT(setRatio(double)));
    connect(ui.variance, SIGNAL(valueChanged(double)), this, SLOT(setVariance(double)));
    connect(ui.cutMethod, SIGNAL(currentTextChanged(QString)), this, SLOT(setCutMethod(QString)));

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
void Window::openImg(QString fileName)
{
    
    if (fileName.isEmpty())
    {
        return;
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
            return;
        }
        //ui->label->setPixmap(QPixmap::fromImage(*img));
    }
}

/** Save a image file.
  * @author CuiYuxin YangYaocheng */
void Window::saveFile()
{
    // TODO
}

/** Open an about Window.
  * @author CuiYuxin YangYaocheng */
void Window::about()
{
    QString content = "\t灰度图像表示STC和RNAM算法。STC算法是一种基于S-树的空间数据结构的灰度图像表示方法。\n\t作者：崔钰薪、杨曜诚、周通宇、罗智豪\n\t本程序遵循MIT开源协议，项目地址：https://github.com/SCUT-CS/Project-1";
    QMessageBox aboutWindow(QMessageBox::NoIcon, QString("关于"), content);
    //aboutWindow.setIconPixmap("xxxxxxxxxxxxxxxxxxxxxxx.png");
    aboutWindow.exec();
}


