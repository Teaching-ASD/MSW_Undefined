#include "MarkedMap.h"

MarkedMap::MarkedMap(std::string filename):Map(filename){
}

std::vector<int> MarkedMap::getHeroPosition() const{

    std::vector<int> ret;


    for(unsigned int y = 0 ; y < mapvector.size(); y++ ){
        for(unsigned int x = 0 ; x < mapvector[y].size(); x++){
            if(mapvector[y][x]=='H'){
                ret.push_back(x);
                ret.push_back(y);
                return ret;
            }
        }
    }
    return ret;
};

std::vector<int> MarkedMap::getMonsterPositions(char c) const{

    std::vector<int> ret;


    for(unsigned int y = 0 ; y < mapvector.size(); y++ ){
        for(unsigned int x = 0 ; x < mapvector[y].length(); x++)
            if(mapvector[y][x]==c){
                ret.push_back(x);
                ret.push_back(y);
            }
    }

    return ret;

};
