#include "Arena.h"

Arena::Arena(Hero* hero1,Hero* hero2)
{
    heroes.push_back(hero1);
    heroes.push_back(hero2);

}

Arena::~Arena()
{
    heroes.clear();
}
