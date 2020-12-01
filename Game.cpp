#include "Game.h"

Game::Game() {};

Game::Game(std::string mapfilename){

Map* map_= new Map(mapfilename) ;
map = map_;

}

void Game::setMap(Map& map_){

    if(monstersV.size() > 0 || heroPos != nullptr ){

        throw AlreadyHasUnitsException(" You can't change the map, because it contains units. ");

    }
    
    delete map;
    this->map = new Map(map_);
    
}

void Game::putHero(Hero hero, int x, int y) {
 
    if(map == nullptr){

        Map::WrongIndexException(" There is no map ");

    }

    if(map->get(x,y)==1){throw OccupiedException(" Occupied block. ");};
    
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

    if(map == nullptr){

        Map::WrongIndexException(" There is no map ");

    }

    if(map->get(x,y)==1){throw OccupiedException(" Occupied block. ");};
    
    if(heroPos!=nullptr){
        if(heroPos->x == x && heroPos->y==y){

            throw OccupiedException(" Occupied block. Here is a Hero.  ");

        }
    }
    

    monstersV.push_back(new Pos(monster,x,y));

};