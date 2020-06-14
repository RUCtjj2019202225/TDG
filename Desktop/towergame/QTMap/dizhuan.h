#ifndef DIZHUAN_H
#define DIZHUAN_H
#include <string>
#include <map>
using namespace std;
class dizhuan{
public:
    static int GRID_SIZE;//游戏中一格，相当于图片中多少像素
    static map<int,dizhuan> dizhuan_set;
    static dizhuan find_dizhuan(int type);

    dizhuan(){}
    dizhuan(string type, int x, int y,int w, int h);
    string getTypeName() const{return this->typeName;}
    int getSrcX() const{return this->srcX;}
    int getSrcY() const{return this->srcY;}
    int getWidth() const{return this->width;}
    int getHeight() const{return this->height;}
    bool get_coverable() const{return this->_coverable;}
    bool get_damaging() const{return this->_damaging;}
    bool get_slowing() const{return this->_slowing;}
    bool get_falling() const{return this->_falling;}

protected:
    string typeName;
    int srcX, srcY,width, height;
    bool _coverable = false;
    bool _damaging = false;
    bool _slowing = false;
    bool _falling = false;
};
#endif // DIZHUAN_H
