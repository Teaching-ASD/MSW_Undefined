#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <list>

#include "JSON.h"
#include "Hero.h"
#include "Monster.h"
#include "Game.h"
#include "Map.h"

//advanced
#include "MarkedMap.h"

const std::map<int,std::string> error_messages = {
    { 1 , "Bad number of arguments. Only a single scenario file should be provided or the second argument should be Map.txt ." },
    { 2 , "The provided scenario file is not accessible." },
    { 3 , "The provided scenario file is invalid." },
    { 4 , "JSON parsing error." }
};

void bad_exit(int exitcode){
    std::cerr 
        << (error_messages.count(exitcode) ? error_messages.at(exitcode) : "Unknown error")
        << std::endl;
    exit(exitcode);
}

int main(int argc, char** argv){
    if (argc != 3 && argc != 2 ) bad_exit(1);
    if (!std::filesystem::exists(argv[1])) bad_exit(2);

    std::string hero_file;
    std::list<std::string> monster_files;
    try {
        JSON scenario = JSON::parseFromFile(argv[1]); 
        if (!(scenario.count("hero")&&scenario.count("monsters"))) bad_exit(3);
        else {
            hero_file=scenario.get<std::string>("hero");
            JSON::list monster_file_list=scenario.get<JSON::list>("monsters");
            for(auto monster_file : monster_file_list)
                monster_files.push_back(std::get<std::string>(monster_file));
        }
    } catch (const JSON::ParseException& e) {bad_exit(4);}

    try { 
        Hero hero{Hero::parse(hero_file)};
        std::list<Monster> monsters;
        for (const auto& monster_file : monster_files)
            monsters.push_back(Monster::parse(monster_file));   
      
    if(argv[2]){ 

        std::string s = argv[2];
  
        MarkedMap Mmap(s);

        Game game;

        game.setMap(Mmap.getClearMap());

        std::vector<int> v=Mmap.getHeroPosition();

        game.putHero(hero,v[0],v[1]);

        char c;
        for (int i = 1; i < 4; i++)
        {
        
            v.clear();

            c = '0'+i;

            v = Mmap.getMonsterPositions(c);

            //MarkedMap.txt

            for (unsigned int x = 0; x < v.size(); x += 2)
            {
               if(i==1){ game.putMonster(Monster::parse("Blood_Raven.json"),v[x],v[x+1]);}
               if(i==2) {game.putMonster(Monster::parse("Fallen.json"),v[x],v[x+1]);}
               if(i==3) {game.putMonster(Monster::parse("Zombie.json"),v[x],v[x+1]);}
            }
        
        }

        game.run();

    }
    else{
        //MarkedMap.txt
        std::cout<<"MarkedMap name:"<<std::endl; 
        std::string mapname;
        std::cin>>mapname;

        MarkedMap Mmap(mapname);

        Game game;

        game.setMap(Mmap.getClearMap());

        std::vector<int> v=Mmap.getHeroPosition();

        game.putHero(hero,v[0],v[1]);

        char c;
        for (int i = 1; i < 4; i++)
        {
        
            v.clear();

            c = '0'+i;

            v = Mmap.getMonsterPositions(c);

            //MarkedMap.txt

            for (unsigned int x = 0; x < v.size(); x += 2)
            {
               if(i==1){ game.putMonster(Monster::parse("Blood_Raven.json"),v[x],v[x+1]);}
               if(i==2) {game.putMonster(Monster::parse("Fallen.json"),v[x],v[x+1]);}
               if(i==3) {game.putMonster(Monster::parse("Zombie.json"),v[x],v[x+1]);}
            }
        
        }

        game.run();

    }

    } catch (const JSON::ParseException& e) {bad_exit(4);}
    return 0;
}
