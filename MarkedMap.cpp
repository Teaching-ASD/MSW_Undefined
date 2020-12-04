#include "MarkedMap.h"


MarkedMap::MarkedMap(std::string filename):Mmap(Map(filename)){
}

std::vector<int> MarkedMap::getHeroPosition() const{

    std::vector<int> ret;
    std::vector<std::string> v;

    v = Mmap.getVector();

    for(unsigned int y = 0 ; y < v.size(); y++ ){
        for(unsigned int x = 0 ; x < v[y].size(); x++){
            if(v[y][x]=='H'){
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
    std::vector<std::string> v;

    v = Mmap.getVector();

    for(unsigned int y = 0 ; y < v.size(); y++ ){
        for(unsigned int x = 0 ; x < v[y].length(); x++)
            if(v[y][x]==c){
                ret.push_back(x);
                ret.push_back(y);
            }
    }

    return ret;

};

Map MarkedMap::getClearMap()const{
    
    Map m = this->Mmap;

    for(unsigned int y = 0 ; y < m.mapvector.size(); y++ ){
        for(unsigned int x = 0 ; x < m.mapvector[y].length(); x++){

            if(m.mapvector[y][x]=='1' || m.mapvector[y][x]=='2' || m.mapvector[y][x]=='3' || m.mapvector[y][x]=='H' ){
                m.mapvector[y][x]=' ';
            }
        }
    }

    return m;
};
