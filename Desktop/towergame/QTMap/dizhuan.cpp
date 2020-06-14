#include "dizhuan.h"
#include<iostream>
int dizhuan::GRID_SIZE = 32;

pair<int,dizhuan> dizhuan_pairArray[] =
{
    make_pair(1, dizhuan("grass",2,1, 2, 2)),
    make_pair(2, dizhuan("soil",4,1, 2, 2)),
    make_pair(3, dizhuan("stone",4,4, 2, 2)),
    make_pair(4, dizhuan("flame",4,7, 2, 2)),
    make_pair(5, dizhuan("ice",6,4, 2, 2)),
    make_pair(6, dizhuan("soil_hole",8,1, 2, 2)),
    make_pair(7, dizhuan("ice_hole",10,4, 2, 2))
};

map<int,dizhuan> dizhuan::dizhuan_set(dizhuan_pairArray,dizhuan_pairArray+sizeof(dizhuan_pairArray)/sizeof(dizhuan_pairArray[0]));

dizhuan::dizhuan(string type, int x, int y, int w, int h){
    this->typeName = type;
    this->srcX = x;
    this->srcY = y;
    this->width = w;
    this->height = h;
    if (type.compare("grass")==0){
        this->_coverable = true;
    }

    else if (type.compare("soil")==0){
        this->_coverable = true;
    }
    else if (type.compare("stone")==0){

    }
    else if (type.compare("flame")==0){
        this->_coverable = true;
        this->_damaging = true;
    }
    else if (type.compare("ice")==0){
        this->_coverable = true;
        this->_slowing = true;
    }

    else if (type.compare("soil_hole")==0){
        this->_coverable = true;
        this->_falling = true;
    }
    else if (type.compare("ice_hole")==0){
        this->_coverable = true;
        this->_falling = true;
    }
}

dizhuan dizhuan::find_dizhuan(int type){
    map<int,dizhuan>::iterator kv;
    kv = dizhuan::dizhuan_set.find(type);
    if (kv==dizhuan::dizhuan_set.end()){
       cout<<"Error: cannot find dizhuan"<<endl;
       return dizhuan();
    }
    else{
        return kv->second;
    }
}
