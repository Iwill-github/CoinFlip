#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mymainwindow.h"
#include "coinbutton.h"

class PlayScene : public MyMainWindow
{
    Q_OBJECT
public:
    PlayScene(int level, QWidget *parent = nullptr);
    void flip(int row, int col);        // 翻动 row 行，col列的硬币
    void judgeWin();                    // 判断游戏是否胜利
protected:
    void paintEvent(QPaintEvent *ev);
private:
    CoinButton *mCoins[4][4];           // 硬币按钮组
    bool mHasWin;                       // 胜利标志

signals:
    void backBtnClicked();
};

#endif // PLAYSCENE_H
