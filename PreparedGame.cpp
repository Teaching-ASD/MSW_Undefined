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
        Hero hero{Hero::parse(hero_file)};
        this->setMap(MarkedMap(map_file));
        beeMap = true;
        putHero(hero,map.getHeroPosition().first,map.getHeroPosition().second);
        int i=0;
        std::vector<std::pair<int,int>> monsterpairs;
        for(auto monster_file : monster_file_list)
        {
             i++;

           char c = '0'+i;
            monsterpairs = map.getMonsterPositions(c);

            for (unsigned int x = 0; x < monsterpairs.size(); x ++)
            {
                putMonster(Monster::parse(std::get<std::string>(monster_file)),monsterpairs.at(x).first,monsterpairs.at(x).second);
            }
        }
}

void PreparedGame::run(){
        gameIsRunning = true;
        if(beeMap == false || heroPos==nullptr){ throw Game::NotInitializedException(" Map or Hero is not initialized."); }
        this->step(this->heroPos->x, this->heroPos->y);
        while(monsters.size()!=0 && heroPos->hero->isAlive()){
            //this->lightradius();
            for(Renderer* rend:rendererList){
                rend->render(*this);
            }
            std::string direction;
            std::cout << "Enter a direction!"<<std::endl;
            std::cin >> direction;
            if(direction == "north"){
                this->step(this->heroPos->x, this->heroPos->y-1);

            }else if(direction == "south"){
                this->step(this->heroPos->x, this->heroPos->y+1);

            }else if(direction == "east"){
                this->step(this->heroPos->x+1, this->heroPos->y);

            }else if(direction == "west"){
                this->step(this->heroPos->x-1, this->heroPos->y);
            }else if(direction == "exit"){
                return ;
            }
            else std::cout << "Wrong direction! try again!" << std::endl;
        }
        if(heroPos->hero->isAlive()){
        //this->drawMap();
        std::cout << heroPos->hero->getName() << " cleared the map." << std::endl;
        }
        gameIsRunning = false;

}