#pragma once
class Game;
#include"Game.h"
#include"MarkedMap.h"

class Renderer{
    public: 
    virtual void render(const Game& g) const = 0;
    virtual ~Renderer(){};
};