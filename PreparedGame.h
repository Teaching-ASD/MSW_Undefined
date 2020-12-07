/**
 * \class PreparedGame
 *
 * \brief PreparedGame class
 *
 * This is a PreparedGame class which puts the monsters and the hero on the map, and runs the game loop
 *
 * \author LeviG9901, 97Vix, b3nc301
 * 
 * \version 1.0
 *
 * \date 2020.12.06. 22:07
 *
 * Created on: 2020.12.06. 22:07
*/
#include <string>
#include "Game.h"
#include "JSON.h"
#include "MarkedMap.h"

class PreparedGame:public Game{
    public:
        ///This is a constructor for Prepared Game
        explicit PreparedGame(std::string str_/**< [in] This is a string */);
        ///This is a method for the game run loop
        void run();
};