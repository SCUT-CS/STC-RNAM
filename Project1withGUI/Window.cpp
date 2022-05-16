#include "Window.h"



Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.openFile, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui.saveFile, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui.about, SIGNAL(triggered()), this, SLOT(about()));
}

void Window::openFile()
{
    fileName = QFileDialog::getOpenFileName(this, QString("打开图片"), QDir::homePath(), QString("Images (*.jpg *.bmp *.png *.jpeg *.gif)"));
}

void Window::saveFile()
{
    // TODO
}

void Window::about()
{
    QString content = "// TODO";
    QMessageBox aboutWindow(QMessageBox::NoIcon, QString("关于"), content);
    //aboutWindow.setIconPixmap("xxxxxxxxxxxxxxxxxxxxxxx.png");
    aboutWindow.exec();
}


