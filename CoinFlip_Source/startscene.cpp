#include "startscene.h"
#include <mypushbutton.h>
#include <QTimer>
#include <QSound>           // 需要使用qmake 引入  QT += multimedia

StartScene::StartScene(QWidget *parent)
    : MyMainWindow{parent}
{
    this->setWindowTitle("翻金币");

    MyPushButton *btnStart = new MyPushButton(":/resource/MenuSceneStartButton.png", ":/resource/MenuSceneStartButton.png", this);
    btnStart->resize(114, 114);
    btnStart->move((this->width() - btnStart->width()) / 2, this->height() * 3 / 4 - btnStart->height() / 2);

    // 第二个窗口返回按钮被点击
    connect(&this->mSelectScene, &SelectScene::backBtnClicked, [=](){
        QSound::play(":/resource/BackButtonSound.wav");
        // 第二个窗口的返回按钮点击时，显示当前窗口，隐藏第二个窗口
        this->mSelectScene.hide();
        this->show();
        this->move(this->mSelectScene.x(), this->mSelectScene.y());
    });

    // 开始按钮被点击
    connect(btnStart, &MyPushButton::clicked, [=](){
        QSound::play(":/resource/TapButtonSound.wav");
        // 在上次动画播放完之前，将按钮设置为不可用
        btnStart->setEnabled(false);

        btnStart->moveDown();               // 播放向下的动画
        // 往上走的动画会覆盖掉下走的动画（表现为连击按钮按钮向上移动），所以需要延时
        QTimer::singleShot(150, [=](){
            btnStart->moveUp();             // 播放向上的动画
        });
        QTimer::singleShot(300, [=](){
            btnStart->setEnabled(true);    // 等向上和向下的动画都播放完后再启用按钮

            // 场景转换
            this->hide();                                   // 隐藏当前窗口
            this->mSelectScene.show();                      // 显示第二个窗口
            this->mSelectScene.move(this->x(), this->y());  // 将窗口移动到当前窗口的位置
        });
    });

}




