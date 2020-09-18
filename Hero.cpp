#include "Hero.h"

Hero::Hero(std::string name_,int damage_,int hp_):name(name_), damage(damage_), hp(hp_)
{

}

std::string Hero::getName()
{
    return this->name;
}

int Hero::getDamage()
{
    return this->damage;
}

int Hero::getHp()
{
    return this->hp;
}

void Hero::setHp(int hp_)
{
    hp = hp_;
}

Hero::~Hero()
{

};
