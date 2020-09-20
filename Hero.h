#pragma once
#ifndef HERO_H
#define HERO_H
#include <string>

class Hero
{
private:
        const std::string name;
        int hp;
        const int damage;
public:
        Hero(std::string name_, int hp_,int damage_);
        std::string getName();
        int getDamage();
        int getHp();
        //void setName(string name_);
        //void setDamage(int damage_);
        //void setHp(int hp_);
        void ChangeHP(int dmg_);
        ~Hero();
};
#endif //HERO_H
