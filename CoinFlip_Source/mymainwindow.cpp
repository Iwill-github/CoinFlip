#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include <QPainter>
#include <QPixmap>

MyMainWindow::MyMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("翻金币");                          // 设置窗口标题
    this->setWindowIcon(QIcon(":/resource/Coin0001.png"));  // 设置窗口的icon
    this->setFixedSize(320, 500);                           // 设置窗口固定大小
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

void MyMainWindow::paintEvent(QPaintEvent *ev)
{
    // 绘制背景图片
    QPainter painter(this);     // 以当前窗口作为绘图设备
    QPixmap pixmap(":/resource/MenuSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);
}





