#include "map.h"
#include<iostream>

int Map::GRID_SIZE = 32;
int Map::Cluster_SIZE = 128;
int Map::Mapwidth = 12;
int Map::Mapheight = 8;

vector<vector<int> > Map::plain = {{1,2,1,2,1,2,1,2,1,2,1,2},
                                   {2,1,2,1,2,1,2,1,2,1,2,1},
                                   {1,2,1,2,1,2,1,2,1,2,1,2},
                                   {2,1,2,1,2,1,2,1,2,1,2,1},
                                   {2,1,2,1,2,1,2,1,2,1,2,1},
                                   {1,2,1,2,1,2,1,2,1,2,1,2},
                                   {2,1,2,1,2,1,2,1,2,1,2,1},
                                   {1,2,1,2,1,2,1,2,1,2,1,2}
                                  };
vector<vector<int> > Map::flameland = {{1,2,1,2,1,2,1,2,1,2,1,2},
                                       {2,1,2,1,2,1,2,1,2,1,2,1},
                                       {1,2,1,2,1,2,1,2,1,2,1,2},
                                       {2,1,2,1,2,1,2,1,2,1,2,1},
                                       {2,1,2,1,2,1,2,1,2,1,2,1},
                                       {1,2,1,2,1,2,1,2,1,2,1,2},
                                       {2,1,2,1,2,1,2,1,2,1,2,1},
                                       {1,2,1,2,1,2,1,2,1,2,1,2},
                                      };
vector<vector<int> > Map::iceland = {{1,2,1,2,1,2,1,2,1,2,1,2},
                                     {2,1,2,1,2,1,2,1,2,1,2,1},
                                     {1,2,1,2,1,2,1,2,1,2,1,2},
                                     {2,1,2,1,2,1,2,1,2,1,2,1},
                                     {2,1,2,1,2,1,2,1,2,1,2,1},
                                     {1,2,1,2,1,2,1,2,1,2,1,2},
                                     {2,1,2,1,2,1,2,1,2,1,2,1},
                                     {1,2,1,2,1,2,1,2,1,2,1,2},
                                    };
vector<vector<int> > Map::getmap(string type){
    if (type.compare("plain")==0){
       return Map::plain;
    }
    else if (type.compare("flameland")==0){
       return Map::flameland;
    }
    else if (type.compare("iceland")==0){
       return Map::iceland;
    }
    else{
        //TODO 应由专门的错误日志文件记录
        cout<<"invalid background type."<<endl;
        return vector<vector<int> >();
    }
}
