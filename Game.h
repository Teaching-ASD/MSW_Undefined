#pragma once
#include<string>
#include<vector>


#include "Map.h"
#include "Hero.h"
#include "Monster.h"

struct Pos{
    Hero *hero=nullptr;
    int x = 0;
    int y = 0;
    Pos(Hero *hero_, int x_, int y_):hero(hero_), x(x_),y(y_){
    }
    ~Pos(){delete hero;}
};


struct monsterPos{
    Monster monster;
    int x=0;
    int y=0;
    monsterPos(Monster &monster_, int x_, int y_):monster(monster_), x(x_),y(y_){
    }
};

class Game{

private:
    bool beeMap = false; 
    bool gameIsRunning = false;
    Map map;
    Pos* heroPos = nullptr;
    std::list<monsterPos> monsters;
    void step(int x, int y);
    void drawMap();
public:
    Game();
    //explicit Game(std::string&);
    Game(std::string&);
    void setMap(const Map&);
    void putHero(Hero,int,int);
    void putMonster(Monster,int,int);
    void run();
    void setChInMap(std::list<Monster>&,Hero&,Game&) const;
    void mapCout(std::vector<std::string>)const;




    ~Game(){

        delete heroPos;
        monsters.clear();

    }

        class OccupiedException : public std::runtime_error {
        public:
            explicit OccupiedException(const std::string& msg) : std::runtime_error(msg){};

    };
            class AlreadyHasHeroException : public std::runtime_error {
        public:
            explicit AlreadyHasHeroException(const std::string& msg) : std::runtime_error(msg){};

    };
            class AlreadyHasUnitsException : public std::runtime_error {
        public:
            explicit AlreadyHasUnitsException(const std::string& msg) : std::runtime_error(msg){};

    };
                class NotInitializedException : public std::logic_error {
        public:
            explicit NotInitializedException(const std::string& msg) : std::logic_error(msg){};

    };
                    class GameAlreadyStartedException : public std::logic_error {
        public:
            explicit GameAlreadyStartedException(const std::string& msg) : std::logic_error(msg){};

    };
};