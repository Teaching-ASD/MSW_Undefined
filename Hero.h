#pragma once
#ifndef HERO_H
#define HERO_H
#include <string>
#include<fstream>


class Hero
{
private:
        const std::string name;
        int hp;
        const int damage;
public:
        Hero(const std::string &name_, int hp_,const int damage_);
        std::string getName();
        int getDamage();
        int getCurHP();
        static Hero parseUnitHero(std::string fname);
        //void setName(string name_);
        //void setDamage(int damage_);
        //void setHp(int hp_);
        //void ChangeHP(int dmg_);
        ~Hero();
        
};
#endif //HERO_H
