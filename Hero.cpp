#include "Hero.h"

Hero::Hero(std::string name_,int hp_,int damage_):name(name_), hp(hp_), damage(damage_)
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
