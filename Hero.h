/**
 * \class Hero
 *
 * \ingroup Example package
 *
 * \brief Hero Class
*/
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
        const double cooldown;
        void ChangeHP(int dmg_);
        std::string stringvar;
public:
        Hero(std::string name_, int hp_,int damage_,double cd_);
        std::string getName();
        int getDamage();
        int getHp();
        std::string getStringvar();
        double getCooldown();
        bool endGame(Hero* h2_);
        void Attack(Hero* h2_);
        ~Hero();
        static Hero parseUnit(std::string fname);
};
#endif //HERO_H
