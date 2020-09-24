#pragma once
#ifndef ARENA_H
#define ARENA_H
#include "Hero.h"
#include <vector>
#include <string>


class Arena
{
    public:
        Arena();
        ~Arena();
        void addHero(Hero hero_);
        const std::string Fight();

    protected:

    private:
        std::vector<Hero> heroes;
        std::string stringvar;
        bool endGame();
        void addData();
        void Attack();
};

#endif // ARENA_H
