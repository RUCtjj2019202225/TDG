#ifndef ICON_H
#define ICON_H
#include <string>
#include <map>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
using namespace std;


//将一类图标定位到素材图片上的具体区域
class ICON
{
public:
    static int GRID_SIZE;//游戏中一格，相当于图片中多少像素
    static map<int,ICON> GAME_ICON_SET;
        //确定各类物体子素材图片的位置，高、宽等数据
    static ICON findICON(int type);
    static void LOG(QString strMsg);
        //根据物体类型名找到图标

    ICON(){}
    ICON(int name, float x, float y, float w, float h);
    int getType() const{return this->type;}
    float getSrcX() const{return this->srcX;}
    float getSrcY() const{return this->srcY;}
    float getWidth() const{return this->width;}
    float getHeight() const{return this->height;}

private:
    int type;
    float srcX, srcY, width, height;

};

#endif // ICON_H
