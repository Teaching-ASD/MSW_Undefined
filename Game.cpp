#include "Game.h"
#include<iostream>


MarkedMap Game::getMarkedMap() const{
    return this->map;
}
Pos* Game::getHeroPos() const{
    return this->heroPos;
}
std::list<monsterPos> Game::getMonsters() const{
    return this->monsters;
};


Game::Game(){MarkedMap map;};

Game::Game(std::string& mapfilename):map(MarkedMap(mapfilename)){
    beeMap=true;
}


void Game::setMap(const MarkedMap &map){

    if(monsters.size() > 0 || heroPos != nullptr ){throw AlreadyHasUnitsException(" You can't change the map, because it contains units.");}

    if(gameIsRunning){throw GameAlreadyStartedException("You can't change the map, because the game started");}
    
    this->map = map;
    beeMap=true;
}


void Game::putHero(Hero hero, int x, int y) {
    if(beeMap == false){ throw Map::WrongIndexException(" There is no map loaded.");}
    if(map.get(x,y)==Map::type::Wall){throw OccupiedException(" Occupied block. ");};
    
    if(gameIsRunning) throw GameAlreadyStartedException("You can't change the Hero, because the game started");

    if(heroPos != nullptr){ throw AlreadyHasHeroException(" Map already has a hero." );}
    Hero* hero_ = new Hero(hero);
    heroPos = new Pos(hero_,x,y);
}

void Game::putMonster(Monster monster,int x,int y){

    if(beeMap == false){ throw Map::WrongIndexException(" There is no map loaded."); }

    if(map.get(x,y)==Map::type::Wall){throw OccupiedException(" Occupied block. ");};

    monsters.push_back(monsterPos(monster,x,y));
};
void Game::run(){
        gameIsRunning = true;
        if(beeMap == false || heroPos==nullptr){ throw Game::NotInitializedException(" Map or Hero is not initialized."); }
        this->step(this->heroPos->x, this->heroPos->y);
        while(monsters.size()!=0 && heroPos->hero->isAlive()){
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
        for(Renderer* rend:rendererList){
                rend->render(*this);
            }
        std::cout << heroPos->hero->getName() << " cleared the map." << std::endl;
        }
        gameIsRunning = false;

}

void Game::step(int x, int y){
    if(this->map.get(x,y) == Map::type::Free || this->map.get(x,y) == Map::type::Monster){
        std::list<monsterPos>::iterator i = monsters.begin();
        while(i!=monsters.end()){
            if(i->x == x && i->y==y){
            this->heroPos->hero->fightTilDeath(i->monster);
            i= monsters.erase(i);
            }
            else {++i;}
        }
        if(this->heroPos->hero->isAlive()){
            this->heroPos->x = x;
            this->heroPos->y = y;
        }
        else {
            std::cout << "The hero died."<< std::endl;
        }
    }
    else std::cout << "Wrong direction! This is a wall!"<< std::endl;
}

void Game::registerRenderer(Renderer * r){
        this->rendererList.push_back(r);
}