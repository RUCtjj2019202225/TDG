#include "rpgobj.h"
#include <iostream>

enum icon{none=0,arrow,bullet,thunder,fireball,missle,smoke,boom,repair,upgrade,destroy,
            AT = 11,gun,magicTt,magicTf,missleW,shield,
            moto=21,mcar1,mcar2,mcar3,boss};

void RPGObj::initObj(int type)
{
    //TODO 所支持的对象类型应定义为枚举 done
    this->_icon = ICON::findICON(type);
    this->_pos_x = 0;
    this-> _pos_y = 0;
    this->_range = 0.1;
    this->_speed = 3;

    QImage all;
    switch(type)
    {
        case none:
        {
            all.load(":/pics/arrow.png");
            this->_pic = all.copy(QRect(0,0,0,0));
            break;
        }
        case arrow:
        {
            all.load(":/pics/arrow.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            this->_damage = 1;
            break;
        }
        case bullet:
        {
            all.load(":/pics/bullet.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            this->_damage = 1;
            break;
        }
        case thunder:
        {
            all.load(":/pics/thunder.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            this->_damage = 3;
            this->_range = 1;
            break;
        }
        case fireball:
        {
            all.load(":/pics/fireball.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            this->_damage = 3;
            this->_range = 1;
            break;
        }
        case missle:
        {
            all.load(":/pics/missleup.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            this->_damage = 5;
            this->_range = 1;
            break;
        }
        case smoke:
        {
            all.load(":/pics/smoke.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            break;
        }
        case boom:
        {
            all.load(":/pics/boom.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            break;
        }
        case repair:
        {
            all.load(":/pics/mark.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            break;
        }
        case upgrade:
        {
            all.load(":/pics/mark.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            break;
        }
        case destroy:
        {
            all.load(":/pics/mark.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            break;
        }
        default:
        {
            //TODO 应由专门的错误日志文件记录 done
            QString tip = "invalid ICON type.";
            ICON::LOG(tip);
            return;
        }
    }
}

void RPGObj::show(QPainter * pa){
    float gSize = Map::Cluster_SIZE;
    pa->drawImage(this->_pos_x*gSize,this->_pos_y*gSize,this->_pic);
}

void RPGObj::setPosX(int x){
    this->_pos_x = x;
}
void RPGObj::setPosY(int y){
    this->_pos_y = y;
}


void RPGObj::MoveNextX(){
    float dis_perupdate_1 = Map::Cluster_SIZE*0.1;
    if(this->_pos_x*Map::Cluster_SIZE + dis_perupdate_1*this->_speed >13*Map::Cluster_SIZE)
        return;
    else
        this->_pos_x += (dis_perupdate_1*this->_speed)/Map::Cluster_SIZE;
}

void RPGObj::MoveNextY(){//还未完成
    float dis_perupdate_1 = Map::Cluster_SIZE*0.1;
    if(this->_pos_y*Map::Cluster_SIZE + dis_perupdate_1*this->_speed>8*Map::Cluster_SIZE)
        return;
    else
        this->_pos_y += (dis_perupdate_1*this->_speed)/Map::Cluster_SIZE;
}

void RPGObj::onErase(){
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/2953.mp3"));
    player->setVolume(30);
    player->play();
}

