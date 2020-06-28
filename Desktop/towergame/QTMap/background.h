#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <QMediaPlayer>
#include <QImage>
#include <QPainter>
#include <string>
#include <map>
#include"dizhuan.h"
#include"map.h"
using namespace std;

class Background{
public:
    static int GRID_SIZE;//游戏中一格，相当于图片中多少像素
    Background(){}
    string getTypeName() const{return this->typeName;}
    void initbg(string type);
    void show(QPainter * pa);
    vector<vector<int> >& getLand(){return this->_land;}
    int getWidth() const{return this->width;}
    int getHeight() const{return this->height;}
protected:
    string typeName;
    int width = 24, height = 16;
    vector<vector<int> > _land;
};

#endif // BACKGROUND_H
