#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QString>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    enum MyPushButtonState{
        Normal,
        Pressed,
    };
    MyPushButton(QString normalImg, QString pressedImg, QWidget *parent = nullptr);
    // 往上和往下的两个动画函数
    void moveDown();
    void moveUp();
protected:
    void paintEvent(QPaintEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private:
    // 正常状态的图片，鼠标按下的图片
    QString mNormalImg;
    QString mPressedImg;
    // 按钮状态
    MyPushButtonState mState;
signals:

};

#endif // MYPUSHBUTTON_H
