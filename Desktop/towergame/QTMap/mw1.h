#ifndef MW1_H
#define MW1_H
#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include<QMouseEvent>
#include<QTime>
#include<QTimer>
#include <QLabel>
#include<cmath>
#include <vector>
#include "rpgobj.h"
#include "rpgchar.h"
#include "world.h"
#include "map.h"


namespace Ui {
class MW1;
}

class MW1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MW1(QWidget *parent = 0);
    ~MW1();
    void paintEvent(QPaintEvent *);
    void MonsterGenerator();
    void MonsterMove();
    void Blocked();

    void BattleCry();
    void fight1();
    void fight2();
    void repair();//
    void level_up();//

    int ifCollide(RPGObj *p);
    void ObjMove();

    void missleLauncher(float x, float y);//TODO 结合mousePressEvent  需要将misslew独立写timer

    void mousePressEvent(QMouseEvent *ev);

private:
    Ui::MW1 *ui;
    World _game;
    QTimer *timer;

    int money = 200;
    QLabel *_MoneyLable = new QLabel(this);
    int life = 10;
    QLabel *_LifeLable = new QLabel(this);
    int MonCount = 0;

    const int RewardMoney = 25;
    const int LevelNumber = 1;

    bool MouseDragging = false;
    bool missleTargeting = false;
    RPGChar* dragging = new RPGChar;
};

#endif // MW1_H
