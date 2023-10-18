#include "selectscene.h"
#include <QPushButton>
#include <QPainter>
#include <QMenuBar>
#include "mypushbutton.h"
#include "playscene.h"
#include <QSound>

SelectScene::SelectScene(QWidget *parent)
    : MyMainWindow{parent}
{
    this->setWindowTitle("选择关卡");                           // 设置窗口标题

    // 返回按钮相关
    MyPushButton *btnBack = new MyPushButton(":/resource/BackButton.png",
                                             ":/resource/BackButtonSelected.png", this);
    btnBack->resize(72, 32);
    btnBack->move(this->width() - btnBack->width(), this->height() - btnBack->height());
    connect(btnBack, &QPushButton::clicked, this, &SelectScene::backBtnClicked);    // 信号可以连接信号


    // 关卡按钮20个
    const int rowHeight = 70, colWidth = 70;
    const int xOffset = 25, yOffset = 130;

    for(int i = 0; i < 20; i++){
        MyPushButton *btn = new MyPushButton(":/resource/LevelIcon.png",
                                             ":/resource/LevelIconSelected.png", this);
        btn->setText(QString::number(i + 1));
        btn->resize(57, 57);

        int row = i / 4;
        int col = i % 4;
        int x = xOffset + col * colWidth;   // 列数 * 列宽 + x偏移
        int y = yOffset + row * rowHeight;  // 行数 * 行宽 + y偏移
        btn->move(x, y);

        connect(btn, &MyPushButton::clicked, [=](){
            QSound::play(":/resource/BackButtonSound.wav");
            PlayScene *playScene = new PlayScene(i + 1);
            playScene->setAttribute(Qt::WA_DeleteOnClose);  // 设置palyScene关闭的时候自动释放，以放置内存泄漏

            playScene->show();
            playScene->move(this->x(), this->y());
            this->hide();

            // 同时开始关注 playscene 的信号
            connect(playScene, &PlayScene::backBtnClicked, [=](){
                QSound::play(":/resource/BackButtonSound.wav");
                this->show();
                this->move(playScene->x(), playScene->y());
                playScene->close();
            });
        });
    }
}


void SelectScene::paintEvent(QPaintEvent *ev)
{
    // 绘制背景图片
    QPainter painter(this);     // 以当前窗口作为绘图设备
    painter.translate(0, this->menuBar()->height());

    QPixmap pixmap(":/resource/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);

    // 绘制logo
    QPixmap pixmapLogo(":/resource/Title.png");
    painter.drawPixmap(20, 0, pixmapLogo);
}
