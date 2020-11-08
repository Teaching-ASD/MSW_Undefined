/**
 * \class Hero
 *
 * \brief Hero class
 *
 * This is a Hero class. This contains the maximum and current hp, current damage, current cooldown and XP of the Hero. 
 *
 * \author LeviG9901, 97Vix, b3nc301
 * 
 * \version 1.1
 *
 * \date 2020.10.18. 16:45
 *
 * Created on: 2020.10.16. 18:00
*/
#pragma once
#ifndef Hero_H
#define Hero_H
#include "Character.h"
#include <math.h>
#include "JSON.h"
#include "Monster.h"

class Hero : public Character
{

private:

    int maxHP;
    int XP=0;
    int level=1;
    const int xpperlvl;
    const int hpperlvl;
    const int dmgperlvl;
    const double cdmperlvl;
    std::string stringvar;
    
public:

    /// This is a constructor for Hero
    Hero(const std::string&/**< [in] The Hero's name */,int/**< [in] The Hero's health */, int/**< [in] The Hero's damage */, double/**< [in] The Hero's attackcooldown */,const int/**< [in] The Hero's Experience per Level */, const int /**< [in] The Hero's HealthPoint Bonus per Level */, const int /**< [in] The Hero's Damage Bonus per Level */, const double /**< [in] The Hero's Cooldown Multiplier per Level */);
    /// This method is for parsing the json files. It gets the filename and passes to the json parser. 
    static Hero parse(std::string fname /**< [in] Name of the file */);

    void addXP();
    /// This method is doing the levelup.It is changing the value of the maxhp and current hp, dmg, cooldown
    void levelUp();
    /**
    * \return The Hero's Experience per Level
    */
    const int getXpPerLvl();
    /**
    * \return The Hero's Health Point bonus per Level
    */
    const int getHpPerLvl();
    /**
    * \return The Hero's Damage bonus per Level
    */
    const int getDmgPerLvl();
    /**
    * \return The Hero's Cooldown Multiplier per Level 
    */
    const double getCdmPerLvl();
    
    const int getLevel();

    void fightTilDeath(Monster&);

    const int getMaxHealthPoints();

    /// This method is doing the attack and levelup.
    void Fight(Monster& monster/**< [in] This is the monster*/,Hero& defend,/**< [in] This is the  Hero */bool HeroAttack/**< [in] Is the hero attacking? */);

    ~Hero(){
    };
};
#endif //Hero_H