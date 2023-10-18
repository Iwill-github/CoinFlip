#include "coinbutton.h"
#include <QPainter>

CoinButton::CoinButton(QWidget *parent)
    : QPushButton{parent}
{
    // 初始状态设置
    this->setState(0);

    // 设置按钮不规则样式，去掉边框
    this->setStyleSheet("QPushButton{border:0px}");

    // 动画的定时器信号和槽的实现
    connect(&this->mTimer, &QTimer::timeout, [=](){
        if(this->mState)
            this->mFrame--; // 银币翻金币
        else
            this->mFrame++; // 金币翻银币

        // 加载相应的图片
        QString frame = QString(":/resource/Coin000%1.png").arg(this->mFrame);
        this->setIcon(QIcon(frame));
        if(this->mFrame >= 8 || this->mFrame <= 1)
            this->mTimer.stop();
    });

}

int CoinButton::state() const
{
    return this->mState;
}

void CoinButton::setState(int newState)
{
    mState = newState;
    if(this->mState){
        this->setIcon(QIcon(":/resource/Coin0001.png"));   // 金币
    }else{
        this->setIcon(QIcon(":/resource/Coin0008.png"));   // 银币
    }

    // 设置icon大小为当前按钮大小
    this->setIconSize(this->size());
}

void CoinButton::setStateWithAnimation(int state)
{
    this->mState = state;
    if(this->mState)        // 本来是0，被设置成了1，所以是银币翻金币的过程
        this->mFrame = 8;   // 完成银币翻金币的过程
    else
        this->mFrame = 1;   // 完成金币翻银币的过程

    this->mTimer.start(30); // 开始定时器计时
}

void CoinButton::flip()
{
//    this->setState(!this->state());
    this->setStateWithAnimation(!this->state());
}


void CoinButton::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);     // 将this设置为绘图设备
    QPixmap pixmap;
    pixmap.load(QString(":/resource/BoardNode.png"));
    painter.drawPixmap(0, 0, pixmap);

    // 调用父类的 paintEvent，父类 paintEvent 中设置了 icon
    QPushButton::paintEvent(ev);
}
