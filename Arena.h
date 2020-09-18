#ifndef ARENA_H
#define ARENA_H
#include "Hero.h"
#include <vector>

class Arena
{
    public:
        Arena(Hero*,Hero*);
        ~Arena();

    protected:

    private:
        std::vector<Hero*> heroes;

};

#endif // ARENA_H
