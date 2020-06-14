#include "icon.h"
#include<iostream>
int ICON::GRID_SIZE = 32;

enum icon{none=0,arrow,bullet,thunder,fireball,missle,smoke,boom,repair,upgrade,destroy,
            AT = 11,gun,magicTt,magicTf,missleW,shield,
            moto=21,mcar1,mcar2,mcar3,boss};

pair<int,ICON> pairArray[] =
{
    make_pair(0,ICON(none,0,0,0,0)),

    make_pair(1,ICON(arrow,0,0, 2,1)),
    make_pair(2,ICON(bullet,0,0, 1,1)),
    make_pair(3,ICON(thunder,0,0, 2,3)),
    make_pair(4,ICON(fireball,3,0, 4,3)),
    make_pair(5,ICON(missle,0,0, 3, 2)),
    make_pair(6,ICON(smoke,6,0, 2, 2)),
    make_pair(7,ICON(boom,24.5,0, 3, 3)),

    make_pair(8,ICON(repair,4,9, 1, 1)),
    make_pair(9,ICON(upgrade,3,6, 1, 1)),
    make_pair(10,ICON(destroy,1,13, 1, 2)),

    make_pair(11,ICON(AT,0,0, 4, 4)),
    make_pair(12,ICON(gun,25,3.5, 3, 2)),
    make_pair(13,ICON(magicTt,0.2,9.3, 1, 2)),
    make_pair(14,ICON(magicTf,0.2,12, 1, 2)),
    make_pair(15,ICON(missleW,0,0, 2, 2)),
    make_pair(16,ICON(shield,0,0, 4, 4)),

    make_pair(21,ICON(moto,0,9, 2, 2)),
    make_pair(22,ICON(mcar1,0,13, 2, 2)),
    make_pair(23,ICON(mcar2,0,13, 2, 2)),
    make_pair(24,ICON(mcar3,0,10,2, 2)),
    make_pair(25,ICON(boss,0,0, 8, 8))
};

map<int,ICON> ICON::GAME_ICON_SET(pairArray,pairArray+sizeof(pairArray)/sizeof(pairArray[0]));


ICON::ICON(int type, float x, float y, float w, float h){
    this->type = type;
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

void ICON::LOG(QString strMsg){
    QFile file("./Log.txt");
    if(!file.open(QFile::WriteOnly | QFile::Append))
        return;
    QTextStream textStream(&file);
    QString msg = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    msg = msg+" "+strMsg;
    textStream<<msg<<"\r\n";
    file.flush();
    file.close();
}
