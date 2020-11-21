#include "Map.h"
#include <fstream>

Map::Map(std::string filename)
{
    std::ifstream file;
    file.open(filename);
    if(!file.is_open())
    {
        throw "The file not exists";
    }
    std::string line;
    while(getline(file,line))
    {
        mapvector.push_back(line);
    }
    file.close();
}

Map::type Map::get(int x, int y) const
{

    if(y > mapvector.size() || x > mapvector[y].length()||y < 0 || x <0)
    {
        throw "Wrong Index Exception";
    }
    else
    {
        if(mapvector[y][x] == ' ')
        {
            Map::type a = Free;
            return a;
        }
        else
        {
            Map::type a = Wall;
            return a;
        }
    }
}

