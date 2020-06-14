#ifndef MAP1_H
#define MAP1_H
#include "dizhuan.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

class Map
{
public:
    static int GRID_SIZE;
    static int Cluster_SIZE;
    static int Mapwidth;
    static int Mapheight;
    static vector<vector<int> > plain;
    static vector<vector<int> > flameland;
    static vector<vector<int> > iceland;
    static vector<vector<int> > getmap(string type);
};

#endif // MAP1_H
