  
#include<string>
#include "Map.h"

class MarkedMap: public Map{


public:
    MarkedMap(std::string);
    MarkedMap(){};

    std::vector<int> getHeroPosition() const;
    std::vector<int> getMonsterPositions(char) const;

};