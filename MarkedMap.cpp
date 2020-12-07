#include "MarkedMap.h"
#include<iostream>

MarkedMap::MarkedMap(const std::string filename):Map(filename){
}

std::pair<int,int> MarkedMap::getHeroPosition() const{
    std::pair<int,int> ret;
    for(unsigned int y = 0 ; y < mapvector.size(); y++){
        for(unsigned int x = 0 ; x < mapvector[y].size(); x++){
            if(mapvector[y][x]=='H'){
                ret=std::make_pair(x,y);
                return ret;
            }
        }
    }
    return ret;
};

std::vector<std::pair<int,int>> MarkedMap::getMonsterPositions(char c) const{

    std::vector<std::pair<int,int>> ret;

    for(unsigned int y = 0 ; y < mapvector.size(); y++ ){
        for(unsigned int x = 0 ; x < mapvector[y].size(); x++){
            if(mapvector[y][x]==c){
                std::pair<int,int> pair = std::make_pair(x,y);
                ret.push_back(pair);
            }
    }
    }
    return ret;

};
