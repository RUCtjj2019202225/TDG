#include "mw1.h"
#include "ui_mw1.h"
#include<math.h>
#include <iostream>
using namespace std;

#define DistBetPoints(X1, Y1, X2, Y2)           \
abs(sqrt((((X1) - (X2)) * ((X1) - (X2))) + (((Y1) - (Y2)) * ((Y1) - (Y2)))))
enum maptype{plain=1,flameland,iceland};
enum dizhuantype{grass=1,soil,stone,flame,ice,soil_hole,ice_hole};
enum cost{AT1_2=50,gun1_2=50,AT0_1=100,gun0_1=100,magicTt0_1=150,magicTf0_1=200,missleW0_1=250,shield0_1=100,repair2=50};
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
    switch(LevelNumber)
    {
    case(plain):
        _game.initWorld("plain");//DONE 应该是输入有效的地图文件
        break;
    case(flameland):
        _game.initWorld("flameland");
        break;
    case(iceland):
        _game.initWorld("iceland");
        break;
    default:
        break;
    }

    _MoneyLable->move(0, 0);
    _MoneyLable->resize(256,64);
    _MoneyLable->setStyleSheet("color:yellow");
    _MoneyLable->setFont(QFont("微软雅黑", 12));

    _LifeLable->move(0, 64);
    _LifeLable->resize(256,64);
    _LifeLable->setStyleSheet("color:red");
    _LifeLable->setFont(QFont("微软雅黑", 12));
    _LifeLable->setText(QString("生命：%1").arg(this->_game.getLife()));

    timer = new QTimer(this);
    timer->start(2000);
    connect(timer,&QTimer::timeout,[=](){
        this->MonsterGenerator();
        fight1();//fight1存在加攻速，需重建timer允许刷新
        fight2();
        Blocked();
        update();
    });
    QTimer* timer0 = new QTimer(this);
    timer0->start(200);
    connect(timer0,&QTimer::timeout,[=](){
        _MoneyLable->setText(QString("金钱：%1").arg(this->_game.getMoney()));
        _LifeLable->setText(QString("生命：%1").arg(this->_game.getLife()));
        MonsterMove();
        BattleCry();//攻击检测
        MonsterDeath();
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
        this->dragging->show(pa);
    }
    if(this->functionDisplay){//如果选中防御塔，显示升级选项
        QImage all,ima;
        all.load(":/pics/mark.png");
        ima = all.copy(QRect(ICON::findICON(8).getSrcX()*ICON::GRID_SIZE, ICON::findICON(8).getSrcY()*ICON::GRID_SIZE, ICON::findICON(8).getWidth()*ICON::GRID_SIZE, ICON::findICON(8).getHeight()*ICON::GRID_SIZE));
        pa->drawImage(QPointF((dragging->getPosX()-0.5)*Cluster_SIZE,(dragging->getPosY()-0.5)*Cluster_SIZE),ima);
        ima = all.copy(QRect(ICON::findICON(9).getSrcX()*ICON::GRID_SIZE, ICON::findICON(9).getSrcY()*ICON::GRID_SIZE, ICON::findICON(9).getWidth()*ICON::GRID_SIZE, ICON::findICON(9).getHeight()*ICON::GRID_SIZE));
        pa->drawImage(QPointF((dragging->getPosX()-0)*Cluster_SIZE,(dragging->getPosY()-0.5)*Cluster_SIZE),ima);
        ima = all.copy(QRect(ICON::findICON(10).getSrcX()*ICON::GRID_SIZE, ICON::findICON(10).getSrcY()*ICON::GRID_SIZE, ICON::findICON(10).getWidth()*ICON::GRID_SIZE, ICON::findICON(10).getHeight()*ICON::GRID_SIZE));
        pa->drawImage(QPointF((dragging->getPosX()+0.5)*Cluster_SIZE,(dragging->getPosY()-0.5)*Cluster_SIZE),ima);
    }

    pa->end();
    delete pa;
}


void MW1::mousePressEvent(QMouseEvent *ev){
   if (ev->button() != Qt::LeftButton){
       functionDisplay = false;
       MouseDragging = false;
       dragging->initChar(0);
       return;
   }
   else{
        int x = ev->x()/Map::Cluster_SIZE;
        int y = ev->y()/Map::Cluster_SIZE;
        if(x>=2&&x<=7&&y==0){
            MouseDragging = true;
            functionDisplay = false;
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
            if(functionDisplay&&dragging->getCharType()==15){
                this->_game.ObjGenerate(5,x,y-1,x,y);
                return;
            }
            if(this->_game.getBF()[x-1][y-1] == 0){
                if(functionDisplay&&dragging->getCharType()!=0){
                    if(ev->y()>=(dragging->getPosY()-0.5)*Cluster_SIZE&&ev->y()<=dragging->getPosY()*Cluster_SIZE){
                        if(ev->x()>=(dragging->getPosX()-0.5)*Cluster_SIZE&&ev->x()<=dragging->getPosX()*Cluster_SIZE){
                            for(auto &p:this->_game.getAllys()){
                               if(p->getPosX() == dragging->getPosX() && p->getPosY() == dragging->getPosY()){
                                   repair(p);
                               }
                            }
                        }
                        else if(dragging->getPosX()*Cluster_SIZE && ev->x()<=(dragging->getPosX()+0.5)*Cluster_SIZE){
                            for(auto &p:this->_game.getAllys()){
                               if(p->getPosX() == dragging->getPosX() && p->getPosY() == dragging->getPosY()){
                                   level_up(p);
                               }
                            }
                        }
                        else if(ev->x()>(dragging->getPosX()+0.5)*Cluster_SIZE&&ev->x()<=(dragging->getPosX()+1)*Cluster_SIZE){
                            for(auto &p:this->_game.getAllys()){
                                    if(p->getPosX() == dragging->getPosX() && p->getPosY() == dragging->getPosY()){
                                        this->_game.eraseChar(p);
                                    }
                            }
                        }
                    }
                }
                functionDisplay = false;
                if(MouseDragging){
                    if(this->_game.getBG().getLand()[x-1][y-1]!=3){
                        dragging->setPosX(ev->x()/Map::Cluster_SIZE);
                        dragging->setPosY(ev->y()/Map::Cluster_SIZE);
                        this->_game.CharGenerate(dragging->getCharType(),dragging->getPosX(),dragging->getPosY());
                        switch(dragging->getCharType())
                        {
                        case AT:
                            if(this->_game.getMoney()>=AT0_1){
                                this->_game.setMoney(this->_game.getMoney() - AT0_1);
                            }
                            break;
                        case gun:
                            if(this->_game.getMoney()>=gun0_1){
                                this->_game.setMoney(this->_game.getMoney() - gun0_1);
                            }
                            break;
                        case magicTt:
                            if(this->_game.getMoney()>=magicTt0_1){
                                this->_game.setMoney(this->_game.getMoney() - magicTt0_1);
                            }
                            break;
                        case magicTf:
                            if(this->_game.getMoney()>=magicTf0_1){
                                this->_game.setMoney(this->_game.getMoney() - magicTf0_1);
                            }
                            break;
                        case missleW:
                            if(this->_game.getMoney()>=missleW0_1){
                                this->_game.setMoney(this->_game.getMoney() - missleW0_1);
                            }
                            break;
                        case shield:
                            if(this->_game.getMoney()>=shield0_1){
                                this->_game.setMoney(this->_game.getMoney() - shield0_1);
                            }
                            break;
                        }
                        update();
                        dragging->initChar(0);
                        MouseDragging = false;
                        this->setMouseTracking(false);
                    }
                }

            }
            else{
                MouseDragging = false;
                dragging->initChar(0);
                for(auto &p:this->_game.getAllys()){
                    if(p->getPosX() == x && p->getPosY() == y){
                        functionDisplay = true;
                        dragging->initChar(p->getCharType());
                        dragging->setPosX(p->getPosX());
                        dragging->setPosY(p->getPosY());
                        update();
                    }
                }
            }
        }

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
        this->_game.CharGenerate(21,13,y);
    else if(MonCount>=10&&MonCount<20)
        this->_game.CharGenerate(22,13,y);
    else if(MonCount>=20&&MonCount<30)
        this->_game.CharGenerate(23,13,y);
    else if(MonCount>=30&&MonCount<40)
        this->_game.CharGenerate(24,13,y);
    else if(MonCount==40)
        this->_game.CharGenerate(25,13,4);

    MonCount++;
}

void MW1::Blocked(){
    for(auto &pm:this->_game.getMonsters()){
        pm->setBlocked(false);
        pm->setAlart(false);
        for(auto &pa:this->_game.getAllys()){
            if(pm->getPosX() - pa->getPosX() <= 1 && pm->getPosY() == pa->getPosY()){
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
        if(this->_game.getMonsters()[i]->getPosX()<1){
            this->_game.setLife(this->_game.getLife() - 1);
            this->_game.eraseChar(this->_game.getMonsters()[i]);
        }
        int x = this->_game.getMonsters()[i]->getPosX()-1,y = this->_game.getMonsters()[i]->getPosY()-1;
        if(this->_game.getBG().getLand()[y][x] == ice_hole||this->_game.getBG().getLand()[y][x] == soil_hole){
            this->_game.eraseChar(this->_game.getMonsters()[i]);
        }
        else if(this->_game.getBG().getLand()[y][x] == flame){
            this->_game.getMonsters()[i]->setBlood(this->_game.getMonsters()[i]->getBlood() - 0.1);
        }
        else if(this->_game.getBG().getLand()[y][x] == ice){
            this->_game.getMonsters()[i]->setSpeed(this->_game.getMonsters()[i]->getNormalSpeed()*0.5);
        }
        else
            this->_game.getMonsters()[i]->setSpeed(this->_game.getMonsters()[i]->getNormalSpeed());
    }

}
void MW1::MonsterDeath(){
    for(auto &pm:this->_game.getMonsters()){
        if(pm->getBlood() < 1e-5){
            for(auto &pa:this->_game.getAllys()){
                for(auto &a:pa->getAims()){
                    if(a==pm)
                        pa->delAims(pm);
                }
            }
            this->_game.eraseChar(pm);
        }
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
                for(int i = 0;i<p->getAttackSpeed();i++){
                    this->_game.ObjGenerate(arrow,p->getPosX()+0.9-0.1*i,p->getPosY()+0.3);
                }
                break;
            case gun:
                for(int i = 0;i<p->getAttackSpeed();i++){
                    this->_game.ObjGenerate(bullet,p->getPosX()+0.9-0.1*i,p->getPosY()+0.3);
                }
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
                    this->_game.ObjGenerate(thunder,p->getAims().back()->getPosX(),p->getAims().back()->getPosY()-1,p->getAims().back()->getPosX(),p->getAims().back()->getPosY());
                break;
            case magicTf:
                if(!p->getAims().empty())
                    this->_game.ObjGenerate(fireball,p->getAims().back()->getPosX(),p->getAims().back()->getPosY()-1,p->getAims().back()->getPosX(),p->getAims().back()->getPosY());
                break;
            default:
                    break;
            }
            update();
        }
    }
}

int MW1::ifCollide(RPGObj*p){
    if(p->getObjType() == 4 ||p->getObjType() == 5){
        if(p->getPosX() == p->getTarPosX()&&p->getPosY() == p->getTarPosY()){
            for(auto &pm:this->_game.getMonsters()){
                if(sqrt((pm->getPosX() - p->getPosX())*(pm->getPosX() - p->getPosX()) + (pm->getPosY() - p->getPosY())*(pm->getPosY() - p->getPosY()))< p->getRange()){
                    pm->setBlood(pm->getBlood() - p->getDamage());
                }
            }
            p->setIfCollide(true);
        }

    }
    else{
        for(auto &pm:this->_game.getMonsters()){
            if(sqrt((pm->getPosX() - p->getPosX())*(pm->getPosX() - p->getPosX()) + (pm->getPosY() - p->getPosY())*(pm->getPosY() - p->getPosY()))< p->getRange()+ 0.3){
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
    }

    update();
    if(p->getIfCollide()){
        return 1;
    }
    else
        return 0;
}

void MW1::ObjMove(){
    for(auto &p:this->_game.getObjects()){
        if(ifCollide(p)){
            this->_game.eraseObj(p);
            update();
        }
        else{
            if(p->getObjType()<=2)
                p->MoveNextX();
            else if(p->getObjType()>=3&&p->getObjType()<=5)
                p->MoveNextY();
            if(p->getPosX()>13 || p->getPosY()>9)
                this->_game.eraseObj(p);
        }
    }
}


void MW1::level_up(RPGChar* p){
    if(p->getCharType()==11||p->getCharType()==12){
        if(p->getGrade()<p->getMaxGrade()){
            p->setAttactkSpeed(2);
            p->setGrade(p->getGrade()+1);
            if(p->getCharType()==11){
                this->_game.setMoney(this->_game.getMoney()- AT1_2);
            }
            else{
                this->_game.setMoney(this->_game.getMoney()- gun1_2);
            }
        }
        update();
     }
}
void MW1::repair(RPGChar* p){
    if(p->getBlood() == p->getMaxBlood())
        return;
    else if(p->getBlood() == p->getMaxBlood()-1)
        p->setBlood(p->getMaxBlood());
    else
        p->setBlood(p->getBlood()+2);
    this->_game.setMoney(this->_game.getMoney()- repair2);
    update();
}
