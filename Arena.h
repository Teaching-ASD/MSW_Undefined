#ifndef ARENA_H
#define ARENA_H
#include "Hero.h"
#include <vector>

class Arena
{
    public:

        Arena(Hero*,Hero*);
        const bool getEnd();
        const std::string getData(std::string);
        std::string Attack();
        ~Arena();

    protected:

    private:
        std::vector<Hero*> heroes;

};

#endif // ARENA_H
