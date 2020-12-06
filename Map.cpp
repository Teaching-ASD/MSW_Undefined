#include "Map.h"
#include <fstream>


Map::Map(){};


Map::Map(std::string filename)
{
    long unsigned int max=0;
    std::ifstream file;
    file.open(filename);
    if(!file.is_open())
    {
        throw "The file not exists";
    }
    std::string line;
    while(getline(file,line))
    {
        if(line.size()>max){max=line.size();}
        mapvector.push_back(line);

    }
    for(long unsigned int i=0;i<mapvector.size();i++){
        mapvector.at(i).pop_back();
        while(mapvector.at(i).size()<=max){
            mapvector.at(i)+="#";
        }
    }
    file.close();
}


Map::type Map::get(long unsigned int x, long unsigned int y) const
{
    if(y >= mapvector.size())
    {
        throw WrongIndexException("Y is wrong");
    }
    else if(x >= mapvector[y].size())
    {
        throw WrongIndexException("X is wrong");
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
        
        else if(mapvector[y][x] == 'H')
        {
            Map::type a = Free;
            return a;
        }
        else
        {
            Map::type a = Monster;
            return a;
        }
    }
}