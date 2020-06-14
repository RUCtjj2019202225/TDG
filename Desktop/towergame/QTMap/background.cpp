#include "background.h"
#include"map.h"
#include<iostream>
int Background::GRID_SIZE = 32;

void Background::initbg(string type){
    this->_land = Map::getmap(type);
}
void Background::show(QPainter *pa){
    QImage all;
    all.load(":/pics/7.png");

    dizhuan dz[7];
    for(int i=0;i<7;i++){
        dz[i] = dizhuan::find_dizhuan(i+1);
    }
    QImage _grass,_soil,_stone,_flame,_ice,_soil_hole,_ice_hole,castle;
    _grass    = all.copy(QRect(dz[0].getSrcX()*GRID_SIZE,dz[0].getSrcY()*GRID_SIZE, dz[0].getWidth()*GRID_SIZE, dz[0].getHeight()*GRID_SIZE));
    _soil     = all.copy(QRect(dz[1].getSrcX()*GRID_SIZE,dz[1].getSrcY()*GRID_SIZE, dz[1].getWidth()*GRID_SIZE, dz[1].getHeight()*GRID_SIZE));
    _stone    = all.copy(QRect(dz[2].getSrcX()*GRID_SIZE,dz[2].getSrcY()*GRID_SIZE, dz[2].getWidth()*GRID_SIZE, dz[2].getHeight()*GRID_SIZE));
    _flame    = all.copy(QRect(dz[3].getSrcX()*GRID_SIZE,dz[3].getSrcY()*GRID_SIZE, dz[3].getWidth()*GRID_SIZE, dz[3].getHeight()*GRID_SIZE));
    _ice      = all.copy(QRect(dz[4].getSrcX()*GRID_SIZE,dz[4].getSrcY()*GRID_SIZE, dz[4].getWidth()*GRID_SIZE, dz[4].getHeight()*GRID_SIZE));
    _soil_hole= all.copy(QRect(dz[5].getSrcX()*GRID_SIZE,dz[5].getSrcY()*GRID_SIZE, dz[5].getWidth()*GRID_SIZE, dz[5].getHeight()*GRID_SIZE));
    _ice_hole = all.copy(QRect(dz[6].getSrcX()*GRID_SIZE,dz[6].getSrcY()*GRID_SIZE, dz[6].getWidth()*GRID_SIZE, dz[6].getHeight()*GRID_SIZE));

    all.load(":/pics/castle.png");
    castle    = all.copy(QRect(8*GRID_SIZE,6*GRID_SIZE, 3*GRID_SIZE, 3*GRID_SIZE));
    castle    = castle.scaled(4*GRID_SIZE,4*GRID_SIZE);

    pair<int,QImage> img_pa[] =
    {
        make_pair(1, _grass),
        make_pair(2, _soil),
        make_pair(3, _stone),
        make_pair(4, _flame),
        make_pair(5, _ice),
        make_pair(6, _soil_hole),
        make_pair(7, _ice_hole)
    };
    map<int,QImage> IMG_PA(img_pa,img_pa+sizeof(img_pa)/sizeof(img_pa[0]));

    for(int i=0;i<Map::Mapheight;i++){
        for(int j=0;j<Map::Mapwidth;j++){
            pa->drawImage((j+1)*Map::Cluster_SIZE,(i+1)*Map::Cluster_SIZE,IMG_PA.find(_land[i][j])->second.scaled(Map::Cluster_SIZE,Map::Cluster_SIZE));
        }
    }
    for(int i=1;i<=Map::Mapheight;i++){
        pa->drawImage(0,4*i*GRID_SIZE,castle);
    }
    pa->setBrush(QColor(0, 0, 0));
    pa->drawRect(0,0,1664,128);
}


