#ifndef WORLD_H
#define WORLD_H
#include"background.h"
#include "rpgobj.h"
#include "rpgchar.h"
#include <vector>
#include <string>
#include <QPainter>
#include <QTime>
#include<QTimer>

class World
{
public:
    World(){}
    ~World();
    void initWorld(string map);

    void show(QPainter * pa);
    void showobj(QPainter * pa);
    void showally(QPainter * pa);
    void showmonster(QPainter * pa);

    void CharGenerate(int type, int x,int y);
    void ObjGenerate(int type, float x, float y, float tx = 0, float ty = 0);

    void setMoney(int m){this-> money = m;}
    void setLife(int l){this-> life = l;}

    int getMoney(){return this-> money;}
    int getLife(){return this-> life;}
    vector<RPGChar *>& getMonsters(){return this->_monsters;}
    vector<RPGChar *>& getAllys(){return this->_allys;}
    vector<RPGObj *>& getObjects(){return this->_objs;}
    Background & getBG(){return this->_bg;}
    vector<vector<int> >  & getBF(){return this->battel_field;}

    void eraseObj(RPGObj *p);
    void eraseChar(RPGChar *p);

private:
    int money = 300;
    int life = 12;
    const int RewardMoney = 25;

    Background _bg;
    vector<RPGObj *> _objs;
    vector<RPGChar *> _allys;
    vector<RPGChar *> _monsters;
    vector<vector<int> > battel_field;
};

#endif // WORLD_H
