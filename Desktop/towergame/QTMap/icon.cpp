#include "icon.h"
#include<iostream>
int ICON::GRID_SIZE = 32;

enum Object obj;
enum Charactor charactor;
pair<int,ICON> pairArray[] =
{
    make_pair(1,ICON("player",1,13, 1, 2)),
    make_pair(2,ICON("stone",4,9, 1, 1)),
    make_pair(3,ICON("fruit",3,6, 1, 1))
};

map<int,ICON> ICON::GAME_ICON_SET(pairArray,pairArray+sizeof(pairArray)/sizeof(pairArray[0]));


ICON::ICON(string name, int x, int y, int w, int h){
    this->typeName = name;
    this->srcX = x;
    this->srcY = y;
    this->width = w;
    this->height = h;
}

ICON ICON::findICON(int type){
    map<int,ICON>::iterator kv;
    kv = ICON::GAME_ICON_SET.find(type);
    if (kv==ICON::GAME_ICON_SET.end()){

       cout<<"Error: cannot find ICON"<<endl;
       return ICON();
    }
    else{
        return kv->second;
    }
}
