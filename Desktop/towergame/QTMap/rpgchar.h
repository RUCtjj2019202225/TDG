#ifndef RPGCHAR_H
#define RPGCHAR_H
#include <QMediaPlayer>
#include <QImage>
#include <QPainter>
#include <string>
#include <icon.h>
#include <map>
#include "map.h"
using namespace std;


class RPGChar
{
public:
    RPGChar(){}

    void initChar(int type);
    void show(QPainter * painter);

    int getHeight() const{return this->_icon.getHeight();}
    int getWidth() const{return this->_icon.getWidth();}
    int getCharType() const{return this->_icon.getType();}//返回类名


    void setPosX(int x){this->_pos_x=x;}
    void setPosY(int y){this->_pos_y=y;}
    void setBlood(int blood){this->_now_blood = blood;}
    void setAlart(int alart){this->_alart = alart;}
    void setBlocked(int If){this->_blocked = If;}
    bool getAlart(){return this->_alart;}
    int getPosX() const{return this->_pos_x;}
    int getPosY() const{return this->_pos_y;}
    int getAttack() const{return this->_attack;}
    int getAttackR() const{return this->_attack_r;}
    int getBlood() const{return this->_now_blood;}
    bool ifblocked() const{return this->_blocked;}
    bool ifpaused() const{return this->_paused;}
    bool ifmoving() const{return this->_moving;}

    void MoveNextX();
    void MoveNextY();

    void addAims(RPGChar *mon){this->_aims.push_back(mon);}
    void delAims(RPGChar *mon){
        vector<RPGChar *>::iterator it = find(_aims.begin(), _aims.end(), mon);
        _aims.erase(it);
    }
    vector<RPGChar* > getAims(){return this->_aims;}

    virtual void onErase();


protected:
    //所有坐标，单位均为游戏中的格
    QImage _pic;
    float _pos_x, _pos_y;//该物体在游戏中当前位置（左上角坐标）
    ICON _icon;//可以从ICON中获取对象的素材，尺寸等信息

    int _max_blood;
    int _now_blood;
    int _speed;
    int _attack;
    int _attack_speed;
    int _attack_type;
    int _attack_r;

    bool _blocked = false;
    bool _paused = false;
    bool _moving = true;
    bool _alart = false;

    vector<RPGChar* > _aims;
};

#endif // RPGCHAR_H
