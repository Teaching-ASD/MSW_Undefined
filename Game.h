/**
 * \class Game
 *
 * \brief Game class
 *
 * This is a Game class. This class is controlling the gameplay. 
 *
 * \author LeviG9901, 97Vix, b3nc301
 * 
 * \version 2.0
 *
 * \date 2020.12.06. 21:40
 *
 * Created on: 2020.12.06. 21:40
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
    /**
    * \return This returns the map
    */
    MarkedMap getMarkedMap() const;
    /**
    * \return This returns the Position of the hero
    */
    Pos* getHeroPos() const;
    /**
    * \return This returns the positions of monsters
    */
    std::list<monsterPos> getMonsters() const;
    ///This methos is for adding the Renderer class to the Renderer list
    void registerRenderer(Renderer *);
    /**
    * \return This returns the Wall texture
    */
    std::string getWallTexture() const;
    /**
    * \return This returns the Free texture
    */
    std::string getFreeTexture() const;
private:
friend class Render;
protected:
    ///This is a MarkedMap object
    MarkedMap map;
    ///This is a List of Renderers
    std::list<Renderer*> rendererList;
    ///This is a string contains the WallTexture
    std::string wallTexture;
    ///This is a string contains the FreeTexture
    std::string freeTexture;
    bool beeMap = false; ///This is a bool if the map is readed in or not
    bool gameIsRunning = false;///This is a bool if the game is running or not
    Pos* heroPos = nullptr;///This is a Pos structure which stores the Hero Position
    std::list<monsterPos> monsters;///This is a list which stores the positions of the monsters
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