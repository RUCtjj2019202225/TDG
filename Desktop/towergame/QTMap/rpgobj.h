#ifndef RPGOBJ_H
#define RPGOBJ_H
#include <QMediaPlayer>
#include <QImage>
#include <QPainter>
#include <string>
#include <icon.h>
#include <map>
#include "map.h"
using namespace std;

class RPGObj
{
public:
    RPGObj(){}

    void initObj(int type);
    void show(QPainter * painter);

    int getHeight() const{return this->_icon.getHeight();}
    int getWidth() const{return this->_icon.getWidth();}
    int getObjType() const{return this->_icon.getType();}//返回类名

    void setPosX(float x){this->_pos_x = x;}
    void setPosY(float y){this->_pos_y = y;}
    void setTarPosX(float tx){this->tar_pos_x = tx;}
    void setTarPosY(float ty){this->tar_pos_y = ty;}
    void setIfCollide(int If){this->ifCollide = If;}

    int getPosX() const{return this->_pos_x;}
    int getPosY() const{return this->_pos_y;}
    float getTarPosX(){return this->tar_pos_x;}
    float getTarPosY(){return this->tar_pos_y;}
    int getDamage() const{return this->_damage;}
    float getRange() const{return this->_range;}
    int getSpeed() const{return this->_speed;}
    bool getIfCollide() const{return this->ifCollide;}

    void MoveNextX();
    void MoveNextY();

    virtual void onErase();

protected:
    //所有坐标，单位均为游戏中的格

    QImage _pic;
    float _pos_x, _pos_y;//该物体在游戏中当前位置（左上角坐标）
    float tar_pos_x = 0, tar_pos_y = 0;
    ICON _icon;//可以从ICON中获取对象的素材，尺寸等信息
    float _range;
    int _damage;
    int _speed;
    bool ifCollide = false;

};

#endif // RPGOBJ_H
