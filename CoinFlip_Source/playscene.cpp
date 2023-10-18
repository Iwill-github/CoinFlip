#include "playscene.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QMenuBar>
#include <Qlabel>
#include <coinbutton.h>
#include <dataconfig.h>
#include <QMap>
#include <QTimer>
#include <QMessageBox>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSound>

PlayScene::PlayScene(int level, QWidget *parent)
    : MyMainWindow{parent}
{
    mHasWin = false;
    // 返回按钮相关
    MyPushButton *btnBack = new MyPushButton(":/resource/BackButton.png",
                                             ":/resource/BackButtonSelected.png", this);
    btnBack->resize(72, 32);
    btnBack->move(this->width() - btnBack->width(), this->height() - btnBack->height());
    connect(btnBack, &QPushButton::clicked, this, &PlayScene::backBtnClicked);    // 信号可以连接信号

    // 添加左下角的label
    QLabel *label = new QLabel(this);
    label->resize(150, 50);
    label->setText(QString("Level: %1").arg(level));
    label->setFont(QFont("华文新魏", 18));
    label->move(10, this->height()-label->height() - 10);

    // 16个硬币按钮
    const int colWidth = 50;
    const int rowHeight = 50;
    const int xOffset = 57;
    const int yOffset = 200;

    dataConfig data;
    QVector<QVector<int>> dataMap = data.mData[level];  // 取出第level关的二维数组数据

    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            int x = xOffset + col * colWidth;           // 列数 * 列宽 + x偏移
            int y = yOffset + row * rowHeight;          // 行数 * 行宽 + y偏移
            CoinButton *btn = new CoinButton(this);     // 创建硬币时，设置了一下 "icon" 的大小，默认为银色
            mCoins[row][col] = btn;                     // 存储对应位置的按键指针
            btn->setGeometry(x, y, 50, 50);             // move + resize （此时又设置了一下"btn"的大小，导致icon和）
            btn->setState(dataMap[row][col]);                           // 此时又设置了一下 "icon" 的大小

            // 每次点击硬币的时候就改变状态，状态置反
            connect(btn, &QPushButton::clicked, [=](){
                //btn->flip();
                this->flip(row, col);
            });
        }
    }
}

void PlayScene::flip(int row, int col)
{
    if(mHasWin)
        return;

    QSound::play(":/resource/ConFlipSound.wav");
    this->mCoins[row][col]->flip();
    // 延时翻动相邻硬币
    QTimer::singleShot(200, [=](){
        if(row - 1 >= 0)
            this->mCoins[row - 1][col]->flip();
        if(row + 1 <= 3)
            this->mCoins[row + 1][col]->flip();
        if(col - 1 >= 0)
            this->mCoins[row][col - 1]->flip();
        if(col + 1 <= 3)
            this->mCoins[row][col + 1]->flip();

        // 判断游戏是否胜利
        this->judgeWin();
    });
}

void PlayScene::judgeWin()
{
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            // 有一个是银币就返回
            if(!this->mCoins[row][col]->state())
                return;
        }
    }

    // 所有都是金币的情况下
    //QMessageBox::information(this, "恭喜", "你已经胜利了");

    this->mHasWin = true;           // 设置游戏胜利后，不可以翻转硬币
    // 播放胜利音效
    QSound::play(":/resource/LevelWinSound.wav");
    // 播放胜利动画
    QLabel *labelWin = new QLabel(this);
    QPixmap pix = QPixmap(":/resource/LevelCompletedDialogBg.png");
    labelWin->setPixmap(pix);
    labelWin->resize(pix.size());
    labelWin->show();
    labelWin->move(this->width() / 2 - pix.width() / 2, -labelWin->height());

    QPropertyAnimation *animation = new QPropertyAnimation(labelWin, "geometry", this);
    animation->setStartValue(labelWin->geometry());
    animation->setEndValue(QRect(labelWin->x(), labelWin->y() + 150, labelWin->width(), labelWin->height()));
    animation->setDuration(1000);
    // 设置动画的运动曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    // 动画播放完自动删除动画对象
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void PlayScene::paintEvent(QPaintEvent *ev)
{
    // 绘制背景图片
    QPainter painter(this);     // 以当前窗口作为绘图设备
    painter.translate(0, this->menuBar()->height());

    QPixmap pixmap(":/resource/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);

    // 绘制logo
    QPixmap pixmapLogo(":/resource/Title.png");
    pixmapLogo = pixmapLogo.scaled(pixmapLogo.width() / 2, pixmapLogo.height() / 2);
    painter.drawPixmap(20, 0, pixmapLogo);
}
