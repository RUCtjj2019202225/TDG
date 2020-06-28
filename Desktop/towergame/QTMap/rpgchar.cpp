#include "rpgchar.h"
#include <iostream>

enum icon{none=0,arrow,bullet,thunder,fireball,missle,smoke,boom,repair,upgrade,destroy,
            AT = 11,gun,magicTt,magicTf,missleW,shield,
            moto=21,mcar1,mcar2,mcar3,boss};

void RPGChar::initChar(int type)
{
    this->_icon = ICON::findICON(type);
    this->_pos_x = 9;
    this-> _pos_y = 0;
    this->_normalSpeed = 1;
    this->_speed = this->_normalSpeed;

    QImage all;
    switch (type)
        {
        case none:
            this->_pic = all.copy(0,0,0,0);
            this->_max_blood = 0;
            this->_now_blood = this->_max_blood;
            this->_attack = 0;
            this->_attack_speed =0;
            this->_attack_type = none;
            this->_attack_r = 0;
            break;
        case moto:
            all.load(":/pics/moto.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            this->_max_blood = 2;
            this->_now_blood = this->_max_blood;
            this->_attack = 1;
            this->_attack_speed =1;
            this->_attack_type = none;
            this->_attack_r = 1;
            break;
        case mcar1:
            all.load(":/pics/mcar1.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            this->_max_blood = 2;
            this->_now_blood = this->_max_blood;
            this->_attack = 1;
            this->_attack_speed =1;
            this->_attack_type = 0;
            break;
        case mcar2:
            all.load(":/pics/mcar2.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            this->_max_blood = 2;
            this->_now_blood = this->_max_blood;
            this->_attack = 1;
            this->_attack_speed =1;
            this->_attack_type = 0;
            this->_attack_r = 1;
            break;
        case mcar3:
            all.load(":/pics/mcar3.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            this->_max_blood = 2;
            this->_now_blood = this->_max_blood;
            this->_attack = 1;
            this->_attack_speed =1;
            this->_attack_type = none;
            this->_attack_r = 1;
            break;
        case boss:
            all.load(":/pics/boss0.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            this->_max_blood = 2;
            this->_now_blood = this->_max_blood;
            this->_attack = 1;
            this->_attack_speed =1;
            this->_attack_type = none;
            this->_attack_r = 1;
            break;
        case AT:
            all.load(":/pics/AT1.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            this->_max_blood = 2;
            this->_now_blood = this->_max_blood;
            this->_attack = 1;
            this->_attack_speed =1;
            this->_attack_type = arrow;
            this->_attack_r = 100;
            this->_max_grade = 2;
            break;
        case gun:
            all.load(":/pics/gun.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            this->_max_blood = 2;
            this->_now_blood = this->_max_blood;
            this->_attack = 1;
            this->_attack_speed =1;
            this->_attack_type = bullet;
            this->_attack_r = 100;
            this->_max_grade = 2;
            break;
        case magicTt:
            all.load(":/pics/magicT.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            this->_max_blood = 2;
            this->_now_blood = this->_max_blood;
            this->_attack = 1;
            this->_attack_speed =1;
            this->_attack_type = thunder;
            this->_attack_r = 6;
            break;
        case magicTf:
            all.load(":/pics/magicT.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            this->_max_blood = 2;
            this->_now_blood = this->_max_blood;
            this->_attack = 1;
            this->_attack_speed =1;
            this->_attack_type = fireball;
            this->_attack_r = 6;
            break;
        case missleW:
            all.load(":/pics/missleW.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            this->_max_blood = 2;
            this->_now_blood = this->_max_blood;
            this->_attack = 1;
            this->_attack_speed =1;
            this->_attack_type = missle;
            this->_attack_r = 100;
            this->_alart = true;
            break;
        case shield:
            all.load(":/pics/shield0.png");
            this->_pic = all.copy(QRect(_icon.getSrcX()*ICON::GRID_SIZE, _icon.getSrcY()*ICON::GRID_SIZE, _icon.getWidth()*ICON::GRID_SIZE, _icon.getHeight()*ICON::GRID_SIZE));
            this->_max_blood = 2;
            this->_now_blood = this->_max_blood;
            this->_attack = 1;
            this->_attack_speed =0;
            this->_attack_type = none;
            this->_attack_r = 0;
            break;
        default:
        //TODO 应由专门的错误日志文件记录
            QString tip = "invalid ICON type.";
            ICON::LOG(tip);
            return;
        }



}

void RPGChar::show(QPainter * pa){
    int gSize = Map::Cluster_SIZE;
    float h=this->getHeight(),w=this->getWidth();
    QImage img;
    if(w>h)
        img = this->_pic.scaled(gSize,(h/w)*gSize);
    else
        img = this->_pic.scaled((w/h)*gSize,gSize);
    pa->drawImage(QPointF(this->_pos_x*gSize, this->_pos_y*gSize),img);
}

void RPGChar::MoveNextX(){
    float dis_perupdate_1 = Map::Cluster_SIZE*0.05;
    if(this->_pos_x*Map::Cluster_SIZE-dis_perupdate_1*this->_speed<0.5*Map::Cluster_SIZE)
        return;
    else
        this->_pos_x -= (dis_perupdate_1*this->_speed)/Map::Cluster_SIZE;
}

void RPGChar::MoveNextY(){
    float dis_perupdate_1 = Map::Cluster_SIZE*0.1;
    int i = rand()%2;
    switch(i)
    {
    case(0):{
        if(this->_pos_y*Map::Cluster_SIZE-dis_perupdate_1*this->_speed<1*Map::Cluster_SIZE)
            return;
        else
            this->_pos_y -= dis_perupdate_1*this->_speed;
        break;
    }
    case(1):{
        if(this->_pos_y*Map::Cluster_SIZE+dis_perupdate_1*this->_speed>8*Map::Cluster_SIZE)
            return;
        else
            this->_pos_y += dis_perupdate_1*this->_speed;
        break;
    }
    }
    return;
}

void RPGChar::onErase(){
    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/2953.mp3"));
    player->setVolume(30);
    player->play();
}
