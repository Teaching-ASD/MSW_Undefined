#include "Game.h"

Game::Game():map() {

};

Game::Game(std::string mapfilename): map(Map(mapfilename)), beeMap(true){

}

void Game::setMap(Map& map_){

    if(monstersV.size() > 0 || heroPos != nullptr ){

        throw AlreadyHasUnitsException(" You can't change the map, because it contains units. ");
    }
    this->map = map_;
    beeMap=true;
}




void Game::putHero(Hero hero, int x, int y) {

    if(beeMap == false){ throw Map::WrongIndexException(" There is no map ");}

    if(map.get(x,y)==1){throw OccupiedException(" Occupied block. ");};
    
    for(auto i : monstersV){

        if(i->x == x && i->y==y){

            throw OccupiedException(" Occupied block. Here is a monster.  ");

        }

    }

    if(heroPos != nullptr){ throw AlreadyHasHeroException(" Map has already a hero" );}

    Pos* heroPos_= new Pos(hero,x,y);
    heroPos = heroPos_;
}

void Game::putMonster(Monster monster,int x,int y){

    if(beeMap == false){ throw Map::WrongIndexException(" There is no map "); }

    if(map.get(x,y)==1){throw OccupiedException(" Occupied block. ");};
    
    if(heroPos!=nullptr){
        if(heroPos->x == x && heroPos->y==y){

            throw OccupiedException(" Occupied block. Here is a Hero.  ");

        }
    }
    monstersV.push_back(new Pos(monster,x,y));
};
