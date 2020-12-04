#pragma once
#include<string>
#include "Map.h"

class MarkedMap: public Map{
public:
    explicit MarkedMap(std::string filename);
    MarkedMap(){};

    std::pair<int,int> getHeroPosition() const;
    std::vector<std::pair<int,int>> getMonsterPositions(char) const;

};