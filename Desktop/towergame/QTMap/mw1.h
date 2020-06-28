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
#include"icon.h"
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
    void MonsterDeath();
    void fight1();
    void fight2();
    void repair(RPGChar *p);//
    void level_up(RPGChar *p);//

    int ifCollide(RPGObj *p);
    void ObjMove();

    void mousePressEvent(QMouseEvent *ev);


private:
    Ui::MW1 *ui;
    World _game;
    QTimer *timer;


    QLabel *_MoneyLable = new QLabel(this);
    QLabel *_LifeLable = new QLabel(this);
    int MonCount = 0;

    int LevelNumber = 1;

    bool MouseDragging = false;
    bool functionDisplay = false;
    RPGChar* dragging = new RPGChar;
};

#endif // MW1_H
