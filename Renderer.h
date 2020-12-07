/**
 * \class Renderer
 *
 * \brief Renderer class
 *
 * This is a Renderer abstract class
 *
 * \author LeviG9901, 97Vix, b3nc301
 * 
 * \version 1.0
 *
 * \date 2020.12.06. 22:10
 *
 * Created on: 2020.12.06. 22:10
*/
#pragma once
class Game;
#include"Game.h"
#include"MarkedMap.h"

class Renderer{
    public: 
    ///This is a constructor for the Renderer
    virtual void render(const Game& g/**< [in]  This is a game object reference*/) const = 0;
    ///This is a destructor for the Renderer
    virtual ~Renderer(){};
};