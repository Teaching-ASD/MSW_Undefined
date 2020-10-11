#pragma once
#ifndef ARENA_H
#define ARENA_H
#include "Player.h"
#include <vector>
#include <string>


class Arena
{
    public:
        Arena();
        ~Arena();
        void addHero(Player);
        const std::string Fight();

    protected:

    private:

        std::vector<Player> heroes;

        std::string stringvar;
        bool endGame();
        void Attack();
        
};

#endif // ARENA_H
