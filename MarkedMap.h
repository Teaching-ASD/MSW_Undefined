#include<string>
#include "Map.h"

class MarkedMap{

private:

    Map Mmap;

public:
    MarkedMap(std::string);

    std::vector<int> getHeroPosition() const;
    std::vector<int> getMonsterPositions(char) const;
    Map getClearMap()const;

};