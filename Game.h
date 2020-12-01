#include<string>
#include<vector>

#include "Map.h"
#include "Hero.h"
#include "Monster.h"


struct Pos{

public:
    Hero* hero = nullptr;
    Monster* monster = nullptr;
    int x = 0;
    int y = 0;
public:

    Pos(Hero& hero_, int x_, int y_):hero(&hero_), x(x_),y(y_){
    }
    Pos(Monster& monster_, int x_, int y_):monster(&monster_), x(x_),y(y_){
    }

};

class Game{

public:
    Map* map = nullptr;
    Pos* heroPos = nullptr;
    std::vector<Pos*> monstersV ;
public:
    Game();
    Game(std::string);
    void setMap(Map&);
    void putHero(Hero,int,int);
    void putMonster(Monster,int,int);

    ~Game(){

        //stack vagy heap
        delete map;
        delete heroPos;

        for (int i = monstersV.size()-1; i > -1; i--)
        {
            delete monstersV[i];
        }
        

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


};