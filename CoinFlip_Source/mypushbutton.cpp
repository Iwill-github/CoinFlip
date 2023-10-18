#include "mypushbutton.h"
#include <QPropertyAnimation>
#include <QPainter>
#include <QPixmap>


MyPushButton::MyPushButton(QString normalImg, QString pressedImg, QWidget *parent)
    : QPushButton(parent)
    , mNormalImg(normalImg)
    , mPressedImg(pressedImg)
{
    mState = Normal;
}

void MyPushButton::moveDown()
{
    // 位置大小属性发生变化
    // 给定开始的位置大小属性
    // 给定结束的位置大小属性
    // 给定速度，给定动画时长
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry", this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);    // 动画停止时，删除自身的堆区空间
}

void MyPushButton::moveUp()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry", this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(), this->y() - 10, this->width(), this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);    // 动画停止时，删除自身的堆区空间
}

void MyPushButton::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);     // 将this设置为绘图设备
    QPixmap pixmap;
    if(this->mState == Normal)
        pixmap.load(this->mNormalImg);
    if(this->mState == Pressed)
         pixmap.load(this->mPressedImg);
    painter.drawPixmap(0, 0, pixmap);
    // 绘制按钮的文字
    painter.drawText(0, 0, this->width(), this->height(),
                     Qt::AlignHCenter|Qt::AlignVCenter, this->text());
}

void MyPushButton::mousePressEvent(QMouseEvent *ev)
{
    this->mState = Pressed;
    this->update();
    // 保证信号和槽的功能
    QPushButton::mousePressEvent(ev);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *ev)
{
    this->mState = Normal;
    this->update();
    // 保证信号和槽的功能
    QPushButton::mouseReleaseEvent(ev);
}
