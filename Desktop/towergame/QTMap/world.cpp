#include "world.h"
#include "icon.h"
#include"map.h"
#include "rpgobj.h"
#include "rpgchar.h"
#include <QMediaPlayer>
#include<iostream>
using namespace std;

enum cost{AT1_2=50,gun1_2=50,AT0_1=100,gun0_1=100,magicTt0_1=150,magicTf0_1=200,missleW0_1=250,shield0_1=100,repair2=50};
enum icon{none=0,arrow,bullet,thunder,fireball,missle,smoke,boom,repair,upgrade,destroy,
            AT = 11,gun,magicTt,magicTf,missleW,shield,
            moto=21,mcar1,mcar2,mcar3,boss};

World::~World(){

}

void World::initWorld(string map){
    //TODO 下面的内容应该改为从地图文件装载 done

    this->_bg.initbg(map);
    this->battel_field = {{0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0},
                         };
//战场14*10 = map（bg._land）12*8（Cluster_SIZE） +右面loading area1*16，三面景观

    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/hdl.mp3"));
    player->setVolume(30);
    player->play();


}

void World::CharGenerate(int type, int x, int y){
    RPGChar *p = new RPGChar;
    p->initChar(type);
    p->setPosX(x);
    p->setPosY(y);
    if(type>10&&type<20){
        if(this->battel_field[x-1][y-1] ==0){
            this->battel_field[x-1][y-1] = p->getCharType();//不能重位
            this->_allys.push_back(p);
        }
        else
            return;//窗口警告重位
    }
     else if(type>20){
        this->_monsters.push_back(p);
    }
}

void World::ObjGenerate(int type, float x, float y, float tx , float ty){
    RPGObj *p = new RPGObj;
    p->initObj(type);
    p->setPosX(x);
    p->setPosY(y);
    p->setTarPosX(tx);
    p->setTarPosY(ty);
    if(type>0&&type<8){
        this->_objs.push_back(p);
    }
}

void World::show(QPainter * pa){
    this->_bg.show(pa);
    RPGChar *p = new RPGChar;
    for(int i=11;i<17;i++){
        p->initChar(i);
        p->setPosX(i-9);
        p->setPosY(0);
        p->show(pa);
    }

}

void World::showobj(QPainter * pa){
    int n = this->_objs.size();
    for (int i=0;i<n;i++){
        this->_objs[i]->show(pa);
    }
}//或与可以重合
void World::showally(QPainter * pa){
    int n = this->_allys.size();
    for (int i=0;i<n;i++){
        this->_allys[i]->show(pa);
    }
}//或与可以重合
void World::showmonster(QPainter * pa){
    int n = this->_monsters.size();
    for (int i=0;i<n;i++){
        this->_monsters[i]->show(pa);
    }
}//或与可以重合

void World::eraseObj(RPGObj*p){
    p->onErase();
    vector<RPGObj *>::iterator it = find(_objs.begin(), _objs.end(), p);
    _objs.erase(it);
    delete p;
}

void World::eraseChar(RPGChar *p){
    p->onErase();
    if(p->getCharType()>10&&p->getCharType()<20){
        vector<RPGChar *>::iterator it = find(_allys.begin(), _allys.end(), p);
        this->battel_field[p->getPosX()-1][p->getPosY()-1] = 0;
        _allys.erase(it);

    }
    else if(p->getCharType()>20&&p->getCharType()<30){
        vector<RPGChar *>::iterator it = find(_monsters.begin(), _monsters.end(), p);
        _monsters.erase(it);
        this->money += RewardMoney;

    }
    delete p;
}

