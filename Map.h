#include <fstream>
#include <string>
#include <vector>
#include <exception>

class Map{

private:
    std::vector<std::string> mapvector;

public:

    enum type{
        Free,
        Wall
    };
    Map(std::string filename);

    Map::type get(int x, int y) const;

};