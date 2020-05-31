#include "world.h"
#include "icon.h"
#include"map.h"
#include "rpgobj.h"
#include <QMediaPlayer>
#include<iostream>
using namespace std;

//enum Charactor{scorpion = 1,soldier,jaguar,dragon};
//enum Object{player = 1,stone,fruit,fireball};

World::~World(){
    delete this->_player;
}

void World::initWorld(string map){
    //TODO 下面的内容应该改为从地图文件装载 done
    //player 5 5

    this->_bg.initbg(map);
    this->battel_field = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
                         };
//战场25*16 = map（bg._land）24*16 +loading area1*16
//战场敌人>0,己方<0,绝对值分类型

    this->_player->initObj(player);
    this->_player->setPosX(10);//setposition需要加入战场？？
    this->_player->setPosY(10);

    RPGObj *p1 = new RPGObj;
    p1->initObj(stone);
    p1->setPosX(4);
    p1->setPosY(3);

    RPGObj *p2 = new RPGObj;
    p2->initObj(stone);
    p2->setPosX(6);
    p2->setPosY(5);

    RPGObj *p3 = new Fruit;
    p3->initObj(fruit);
    p3->setPosX(6);
    p3->setPosY(8);

    this->_objs.push_back(p1);
    this->_objs.push_back(p2);
    this->_objs.push_back(p3);

    QMediaPlayer * player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/hdl.mp3"));
    player->setVolume(30);
    player->play();


}

void World::show(QPainter * pa){
    this->_bg.show(pa);
}

void World::showobj(QPainter * pa){
    int n = this->_objs.size();
    for (int i=0;i<n;i++){
        this->_objs[i]->show(pa);
    }
    this->_player->show(pa);
}

void World::eraseObj(int x, int y){
    vector<RPGObj*>::iterator it;
    it = _objs.begin();
    while(it!=_objs.end()){
        int flag1 = ((*it)->getObjType()!="stone"); //不是石头
        int flag2 = ((*it)->getPosX() == x) && ((*it)->getPosY()==y);//位置重叠

        if (flag1 && flag2){
            cout<<(*it)->getObjType()<<endl;
            (*it)->onErase();
            delete (*it);
            it = this->_objs.erase(it);
            break;
         }
        else{
            it++;
        }
    }

}

void World::handlePlayerMove(int direction, int steps){
    int x =  this->_player->getNextX(direction);
    int y = this->_player->getNextY(direction);
    this->eraseObj(x,y);
    this->_player->move(direction, steps);
}

