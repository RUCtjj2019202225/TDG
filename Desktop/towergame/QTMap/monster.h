#ifndef MONSTER_H
#define MONSTER_H
#include <QMediaPlayer>
#include <QImage>
#include <QPainter>
#include<string>
#include <map>
#include"icon.h"
using namespace std;


class Monster
{  
public:
    static int GRID_SIZE;

    Monster(){}
    void initAlly(int type);

    void setPosX(int x) {this->_pos_x = x;}
    void setPosY(int y) {this->_pos_y = y;}
    void show(QPainter * pa);

    int getTypeName() const{return this->_type;}
    int getSrcX() const{return this->srcX;}
    int getSrcY() const{return this->srcY;}
    int getWidth() const{return this->width;}
    int getHeight() const{return this->height;}

    int getMBlood() const{return this->_max_blood;}
    int getNBlood() const{return this->_now_blood;}
    int getAttack() const{return this->_attack;}
    int getAspeed() const{return this->_attack_speed;}

    bool ifblocked() const{return this->_blocked;}
    bool ifpaused() const{return this->_paused;}
    bool ifmoving() const{return this->_moving;}



protected:
    //所有坐标，单位均为游戏中的格
    QImage _pic;
    int _type;
    float srcX, srcY,width, height;
    int _pos_x, _pos_y;

    int _max_blood;
    int _now_blood;
    int _attack;
    int _speed;
    int _attack_speed = 1 ;

    bool _blocked;
    bool _paused;
    bool _moving;
};

#endif // MONSTER_H
