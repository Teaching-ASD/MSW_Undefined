#include "PreparedGame.h"
/*
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
*/
//    if (argc != 2 ) bad_exit(1);
//    if (!std::filesystem::exists(argv[1])) bad_exit(2);
PreparedGame::PreparedGame(std::string str_):Game(){
    std::string map_file;
    std::string hero_file;
    std::list<std::string> monster_files;
        JSON scenario = JSON::parseFromFile(str_);
        map_file=scenario.get<std::string>("map");
        hero_file=scenario.get<std::string>("hero");
        JSON::list monster_file_list;
        monster_file_list.push_back(scenario.get<std::string>("monster-1"));
        monster_file_list.push_back(scenario.get<std::string>("monster-2"));
        monster_file_list.push_back(scenario.get<std::string>("monster-3"));
        for(auto monster_file : monster_file_list)
        {
            monster_files.push_back(std::get<std::string>(monster_file));
        }
        Hero hero{Hero::parse(hero_file)};
        setMap(map_file);
        std::vector<int> v = getHeroPosition();
        putHero(hero,v[0],v[1]);
        char c;
        int i=0;
        for (auto y : monster_files)
        {
            i++;
            v.clear();

            c = '0'+i;
            v = getMonsterPositions(c);

            //MarkedMap.txt

            for (unsigned int x = 0; x < v.size(); x += 2)
            {
                putMonster(Monster::parse(y),v[x],v[x+1]);
            }
        
        }
}