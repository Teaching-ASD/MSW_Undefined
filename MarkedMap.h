  
#include<string>
#include "Map.h"

class MarkedMap: public Map{
protected:
    std::vector<int> getHeroPosition() const;
    std::vector<int> getMonsterPositions(char) const;
public:
    MarkedMap(std::string);
    MarkedMap(){};



};