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
    void ObjGenerate(int type, int x,int y);

    vector<RPGChar *>& getMonsters(){return this->_monsters;}
    vector<RPGChar *>& getAllys(){return this->_allys;}
    vector<RPGObj *>& getObjects(){return this->_objs;}

    void eraseObj(RPGObj *p);
    void eraseChar(RPGChar *p);

private:
    Background _bg;
    vector<RPGObj *> _objs;
    vector<RPGChar *> _allys;
    vector<RPGChar *> _monsters;
    vector<vector<int> > battel_field;
};

#endif // WORLD_H
