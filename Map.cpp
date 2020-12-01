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
    if(x > mapvector[y].size() || x <0)
    {
        throw WrongIndexException("X is wrong");
    }
    if(y > mapvector.size() || y < 0 )
    {
        throw WrongIndexException("Y is wrong");
    }
    else
    {
        if(mapvector[y][x] == ' ')
        {
            Map::type a = Free;
            return a;
        }
        else if(mapvector[y][x] == '#')
        {
            Map::type a = Wall;
            return a;
        }
        else{
            throw WrongIndexException("Not found symbol");
        }
    }
}