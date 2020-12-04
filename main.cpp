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


const std::map<int,std::string> error_messages = {
    { 1 , "Bad number of arguments. Only a single scenario file should be provided or the second argument should be Map.txt ." },
    { 2 , "The provided scenario file is not accessible." },
    { 3 , "The provided scenario file is invalid." },
    { 4 , "JSON parsing error." },
    { 5 , "The map file not exist." }
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
        Game game = Game(s);
        game.setChInMap(monsters,hero);
        game.run();


    }
    else{
        std::cout<<"Map name:"<<std::endl; 
        std::string mapname;
        std::cin>>mapname;
        if(mapname != "exit"){
        if (!std::filesystem::exists(mapname)) bad_exit(5);
        Map map(mapname); //kell exception ,ha nincs fajl dobjon hibat

        Game game;

        game.setMap(map);

        game.setChInMap(monsters,hero);

        game.run();}

    }

    } catch (const JSON::ParseException& e) {bad_exit(4);}
    return 0;
}
