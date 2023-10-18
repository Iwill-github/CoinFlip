#ifndef COINBUTTON_H
#define COINBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>

class CoinButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CoinButton(QWidget *parent = nullptr);

    int state() const;
    void setState(int newState);
    void setStateWithAnimation(int state);
    void flip();    // 硬币置反函数

protected:
    void paintEvent(QPaintEvent *ev);

private:
    int mState;     // 硬币状态，0表示银币，1表示金币     alt + enter，选择 "Generate Getter and Setter"
    int mFrame;     // 记录当前动画帧数
    QTimer mTimer;  // 定时器
signals:

};

#endif // COINBUTTON_H
