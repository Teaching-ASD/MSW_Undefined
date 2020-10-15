#pragma once
#ifndef HERO_H
#define HERO_H
#include <string>
#include "Json.h"

class Hero
{
private:
        const std::string name;
        int hp;
        const int damage;
public:
        Hero(const std::string &name_, int hp_,int damage_);
        std::string getName();
        int getDamage();
        int getHp();
        //void setName(string name_);
        //void setDamage(int damage_);
        //void setHp(int hp_);
        void ChangeHP(int dmg_);
        ~Hero();
        static Hero parseUnit(std::string fname);
};
#endif //HERO_H
