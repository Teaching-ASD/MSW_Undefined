/**
 * \class Game
 *
 * \brief Game class
 *
 * This is a Game class. This class is controlling the gameplay. 
 *
 * \author LeviG9901, 97Vix, b3nc301
 * 
 * \version 1.0
 *
 * \date 2020.12.04. 16:00
 *
 * Created on: 2020.12.04. 16:00
*/
#pragma once
class Renderer;
#include<string>
#include<vector>
#include<list>


#include "MarkedMap.h"
#include "Hero.h"
#include "Monster.h"
#include "Renderer.h"

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
public:
    MarkedMap getMarkedMap() const;
    Pos* getHeroPos() const;
    std::list<monsterPos> getMonsters() const;
    void registerRenderer(Renderer *);
    std::string getWallTexture() const;
    std::string getFreeTexture() const;
private:
friend class Render;
protected:
    MarkedMap map;
    std::list<Renderer*> rendererList;
    std::string wallTexture;
    std::string freeTexture;
    bool beeMap = false; 
    bool gameIsRunning = false;
    Pos* heroPos = nullptr;
    std::list<monsterPos> monsters;
    /// This method is for the Hero position changing with the given direction
    void step(int x, int y);
    /// This is an empty constructor for Game. After this the map has to be setted.
    Game();
    /// This is the constructor with the Map filename.
    explicit Game(std::string&/**< [in] The Map's filename. */);
    /// This is the map setter fuction.
    void setMap(const MarkedMap&/**< [in] The Map object. */);
    /**
     * \exception Game::AlreadyHasUnitsException The map already has units on it.
     * \exception Game::GameAlreadyStartedException The game is already started.
    **/
   ///This function is for put a Hero to the map.
       /**
     * \exception Map::WrongIndexException The map is not loaded.
     * \exception Game::OccupiedException The hero is tried to placed in a wall, or outside the map.
     * \exception Game::GameAlreadyStartedException The hero can't be changed because the game is started.
     * \exception Game::AlreadyHasHeroException The hero can't be placed, because the map already has a hero.
     **/
    void putHero(Hero/**< [in] The hero's object*/,int/**< [in] The x coordinate where the hero is placed*/,int/**< [in] The y coordinate where the hero is placed*/);
    ///This function is for put a Monster to the map.
    /**
     * \exception Map::WrongIndexException The map is not loaded.
     * \exception Game::OccupiedException The monster is tried to placed in a wall, or outside the map.
     **/
    void putMonster(Monster/**< [in] The monster's object*/,int/**< [in] The x coordinate where the monster is placed*/,int/**< [in] The y coordinate where the monster is placed*/);
    ///This function is for run the game.
    void run();
    /**
     * \exception Game::NotInitializedException The map is not initialized, or hero is not placed in it. 
    **/

   ///This is a destructor for the game.
    ~Game(){
        delete heroPos;
        monsters.clear();

        std::for_each (rendererList.begin (), rendererList.end (), deleter<Renderer> ());
        rendererList.clear();
    }

    template<typename T>
        struct deleter : std::unary_function<const T*, void>
        {
        void operator() (const T *ptr) const
        {
            delete ptr;
        }
        };
        ///This is an exception class, which is thrown when an error is happened.

        class OccupiedException : public std::runtime_error {
        public:
            explicit OccupiedException(const std::string& msg) : std::runtime_error(msg){};

    };
        ///This is an exception class, which is thrown when an error is happened.
            class AlreadyHasHeroException : public std::runtime_error {
        public:
            explicit AlreadyHasHeroException(const std::string& msg) : std::runtime_error(msg){};

    };
        ///This is an exception class, which is thrown when an error is happened.

            class AlreadyHasUnitsException : public std::runtime_error {
        public:
            explicit AlreadyHasUnitsException(const std::string& msg) : std::runtime_error(msg){};

    };
        ///This is an exception class, which is thrown when an error is happened.

                class NotInitializedException : public std::logic_error {
        public:
            explicit NotInitializedException(const std::string& msg) : std::logic_error(msg){};

    };
        ///This is an exception class, which is thrown when an error is happened.

                    class GameAlreadyStartedException : public std::logic_error {
        public:
            explicit GameAlreadyStartedException(const std::string& msg) : std::logic_error(msg){};

    };
};