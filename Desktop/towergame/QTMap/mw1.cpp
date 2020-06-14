#include "mw1.h"
#include "ui_mw1.h"
#include <iostream>
using namespace std;

#define DistBetPoints(X1, Y1, X2, Y2)           \
abs(sqrt((((X1) - (X2)) * ((X1) - (X2))) + (((Y1) - (Y2)) * ((Y1) - (Y2)))))
enum maptype{plain=1,flameland,iceland};
enum icon{none=0,arrow,bullet,thunder,fireball,missle,smoke,boom,repair,upgrade,destroy,
            AT = 11,gun,magicTt,magicTf,missleW,shield,
            moto=21,mcar1,mcar2,mcar3,boss};
int Cluster_SIZE = Map::Cluster_SIZE;

MW1::MW1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MW1)
{
    ui->setupUi(this);
    setFixedSize(1664,1152);
    QPainter painter;
    _game.initWorld("plain");//TODO 应该是输入有效的地图文件

    _MoneyLable->move(0, 0);
    _MoneyLable->resize(256,64);
    _MoneyLable->setStyleSheet("color:yellow");
    _MoneyLable->setFont(QFont("微软雅黑", 12));
    _MoneyLable->setText(QString("金钱：%1").arg(money));

    _LifeLable->move(0, 64);
    _LifeLable->resize(256,64);
    _LifeLable->setStyleSheet("color:red");
    _LifeLable->setFont(QFont("微软雅黑", 12));
    _LifeLable->setText(QString("生命：%1").arg(life));

    timer = new QTimer(this);
    timer->start(1000);
    connect(timer,&QTimer::timeout,[=](){
        this->MonsterGenerator();
        BattleCry();//攻击检测
        fight1();//fight1存在加攻速，需重建timer允许刷新
        fight2();
        Blocked();
        update();
    });
    QTimer* timer0 = new QTimer(this);
    timer0->start(200);
    connect(timer0,&QTimer::timeout,[=](){
        MonsterMove();
        ObjMove();
        update();
    });
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//设置随机种子
}

MW1::~MW1()
{
    delete ui;
}

void MW1::paintEvent(QPaintEvent *){
    QPainter *pa;
    pa = new QPainter();
    pa->begin(this);
    this->_game.show(pa);
    this->_game.showobj(pa);
    this->_game.showally(pa);
    this->_game.showmonster(pa);

    if(this->MouseDragging){
        this->dragging->show(pa);//拖动准ally对象

    }


    pa->end();
    delete pa;
}


void MW1::mousePressEvent(QMouseEvent *ev){
   if (ev->button() != Qt::LeftButton){
       MouseDragging = false;
       return;
   }
   else{
        int x = ev->x()/Map::Cluster_SIZE;
        int y = ev->y()/Map::Cluster_SIZE;
        if(x>=2&&x<=7&&y==0){
            MouseDragging = true;
            switch(x)
            {
            case(2):
                dragging->initChar(11);
                break;
            case(3):
                dragging->initChar(12);
                break;
            case(4):
                dragging->initChar(13);
                break;
            case(5):
                dragging->initChar(14);
                break;
            case(6):
                dragging->initChar(15);
                break;
            case(7):
                dragging->initChar(16);
                break;
            default:
                return;
           }
        }
        else if(x>=1&&x<=Map::Mapwidth&&y>=1&&y<=Map::Mapheight){
//TODO: map[x][y]不是石头
            if(MouseDragging==true){
                dragging->setPosX(ev->x()/Map::Cluster_SIZE);
                dragging->setPosY(ev->y()/Map::Cluster_SIZE);
                this->_game.CharGenerate(dragging->getCharType(),dragging->getPosX(),dragging->getPosY());
                dragging->initChar(0);
                MouseDragging = false;
                this->setMouseTracking(false);
            }

        }//开发玉米加农炮 可能需要单独写事件独立私有timer missleTargeting

   }
}


void MW1::MonsterGenerator(){
    vector<int > blank;
    for(int i=1;i<9;i++){
        for(auto &p:this->_game.getMonsters()){
            if(p->getPosY()== i)
                break;
            if(p == this->_game.getMonsters().back())
                blank.push_back(i);
        }
    }
    int y;

    if(blank.empty())
        y = rand()%8+1;
    else
        y = blank[rand()%blank.size()];
    if(MonCount<10)
        this->_game.CharGenerate(21,12,y);
    else if(MonCount>=10&&MonCount<20)
        this->_game.CharGenerate(22,12,y);
    else if(MonCount>=20&&MonCount<30)
        this->_game.CharGenerate(23,12,y);
    else if(MonCount>=30&&MonCount<40)
        this->_game.CharGenerate(24,12,y);
    else if(MonCount==40)
        this->_game.CharGenerate(25,12,4);

    MonCount++;
}

void MW1::Blocked(){
    for(auto &pm:this->_game.getMonsters()){
        pm->setBlocked(false);
        pm->setAlart(false);
        for(auto &pa:this->_game.getAllys()){
            if(pm->getPosX() - pa->getPosX() <= 1 ){
                pm->setBlocked(true);
                pm->setAlart(true);
                pa->setBlood(pa->getBlood() - pm->getAttack());
                if(pa->getBlood() < 1e-5){
                    this->_game.eraseChar(pa);
                }
            }
        }
    }
    return;
}

void MW1::MonsterMove(){
    for(unsigned int i=0;i<this->_game.getMonsters().size();i++){
        if(this->_game.getMonsters()[i]->ifblocked() == 0)
            this->_game.getMonsters()[i]->MoveNextX();
    }
}

void MW1::BattleCry(){
    for(auto &p:this->_game.getAllys()){
        int i = p->getCharType();
        p->setAlart(false);
        switch(i)
        {
        case AT:
            for(auto &pm:this->_game.getMonsters()){
                if(pm->getPosY() == p->getPosY()){
                    p->setAlart(true);
                    break;
                }
            }
            break;
        case gun:
            for(auto &pm:this->_game.getMonsters()){
                if(pm->getPosY() == p->getPosY()){
                    p->setAlart(true);
                    break;
                }
            }
            break;
        case magicTt:
            if(!p->getAims().empty())
                p->setAlart(true);
            else
                p->setAlart(false);
            for(auto &pm:this->_game.getMonsters()){
                if(DistBetPoints(p->getPosX()+0.5*Cluster_SIZE,p->getPosY()+0.5*Cluster_SIZE,pm->getPosX()+0.5*Cluster_SIZE,pm->getPosY()+0.5*Cluster_SIZE) < p->getAttackR()){
                    p->addAims(pm);
                    break;
                }
            }
            break;
        case magicTf:
            for(auto &pm:this->_game.getMonsters()){
                if(DistBetPoints(p->getPosX()+0.5*Cluster_SIZE,p->getPosY()+0.5*Cluster_SIZE,pm->getPosX()+0.5*Cluster_SIZE,pm->getPosY()+0.5*Cluster_SIZE) < p->getAttackR()){
                    p->addAims(pm);
                    break;
                }
            }
            break;
        default:
                break;
        }
        if(!p->getAims().empty()){
            for(auto &pm:p->getAims()){
                if(DistBetPoints(p->getPosX()+0.5*Cluster_SIZE,p->getPosY()+0.5*Cluster_SIZE,pm->getPosX()+0.5*Cluster_SIZE,pm->getPosY()+0.5*Cluster_SIZE) > p->getAttackR())
                    p->delAims(pm);
            }
        }
    update();
    }
}

void MW1::fight1(){
    for(auto &p:this->_game.getAllys()){
        if(p->getAlart()){
            int i = p->getCharType();
            switch(i)
            {
            case AT:
                this->_game.ObjGenerate(arrow,p->getPosX(),p->getPosY());
                break;
            case gun:
                this->_game.ObjGenerate(bullet,p->getPosX(),p->getPosY());
                break;
            default:
                    break;
            }
            update();
        }
    }
}

void MW1::fight2(){
    for(auto &p:this->_game.getAllys()){
        if(p->getAlart()){
            int i = p->getCharType();
            switch(i)
            {
            case magicTt:
                if(!p->getAims().empty())
                    this->_game.ObjGenerate(thunder,p->getAims().back()->getPosX(),p->getAims().back()->getPosY()-1);
                break;
            case magicTf:
                if(!p->getAims().empty())
                    this->_game.ObjGenerate(fireball,p->getAims().back()->getPosX(),p->getAims().back()->getPosY()-1);
                break;
            default:
                    break;
            }
            update();
        }
    }
}

int MW1::ifCollide(RPGObj*p){
    for(auto &pm:this->_game.getMonsters()){
        if(pm->getPosX() - p->getPosX() < p->getRange() && pm->getPosY() - p->getPosY() < p->getRange()){
            pm->setBlood(pm->getBlood() - p->getDamage());
            if(pm->getBlood() < 1e-5){
                for(auto &pa:this->_game.getAllys()){
                    for(auto &a:pa->getAims()){
                        if(a==pm)
                            pa->delAims(pm);
                    }
                }
                this->_game.eraseChar(pm);
            }
            p->setIfCollide(true);
        }
    }

    if(p->getIfCollide()){
        return 1;
    }
    else
        return 0;
}

void MW1::ObjMove(){
    for(auto &p:this->_game.getObjects()){
        if(ifCollide(p))
            this->_game.eraseObj(p);
        else{
            if(p->getObjType()<3)
                p->MoveNextX();
            else if(p->getObjType()>2&&p->getObjType()<6)
                p->MoveNextY();
            if(p->getPosX()>13 || p->getPosY()>9)
                this->_game.eraseObj(p);
        }

    }
}


void MW1::missleLauncher(float x, float y){
    for(auto &p:_game.getAllys()){
        if(p->getCharType() == missleW){
             this->_game.ObjGenerate(missle,x,0);//需要设置私有time区别上升和下降
        }
    }
}
