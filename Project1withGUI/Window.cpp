#include "Window.h"

/** Main window.
  * @author CuiYuxin YangYaocheng */
Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    // TODO 创建文件夹 "./RNAM/" "./STC/"
    connect(ui.openFile, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui.saveFile, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui.about, SIGNAL(triggered()), this, SLOT(about()));
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
    QString content = "// TODO";
    QMessageBox aboutWindow(QMessageBox::NoIcon, QString("关于"), content);
    //aboutWindow.setIconPixmap("xxxxxxxxxxxxxxxxxxxxxxx.png");
    aboutWindow.exec();
}


