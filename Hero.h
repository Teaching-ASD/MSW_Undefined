/**
 * \class Hero
 *
 * \brief Hero class
 *
 * This is a Hero class. This is stores the datas from the Hero. 
 *
 * \author LeviG9901, 97Vix, b3nc301
 * 
 * \version 2.2
 *
 * \date 2020.11.08. 12:25
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
    const double defperlvl;
    int lradius;
    const int lrperlvl = 1;
 
public:

    /// This is a constructor for Hero
    Hero(const std::string&/**< [in] The Hero's name */,int/**< [in] The Hero's health */, int/**< [in] The Hero's Physical damage */,int/**< [in] The Hero's Magical damage */, double/**< [in] The Hero's attackcooldown */,const int/**< [in] The Hero's Experience per Level */, const int /**< [in] The Hero's HealthPoint Bonus per Level */, const int /**< [in] The Hero's Damage Bonus per Level */, const double /**< [in] The Hero's Cooldown Multiplier per Level */,int/**< [in] The Hero's Defense value */, const double/**< [in] The Hero's Defense Bonus per Level */, int/**< [in] The Hero's light radius */,const int/**< [in] The Hero's light radius bonus per level */, const std::string& texture_ /**<[in] The hero's texture*/);
    /// This method is for parsing the json files. It gets the filename and passes to the json parser. 
    static Hero parse(std::string fname /**< [in] Name of the file */);
    /// This method is increasing the xp of the Hero 
    void addXP(int);
    /// This method is doing the levelup.It is changing the value of the maxhp and current hp, dmg, cooldown
    void levelUp();
    /**
    * \return The Hero's Experience per Level
    */
    int getXpPerLvl() const;
    /**
    * \return The Hero's Health Point bonus per Level
    */
    int getHpPerLvl() const;
    /**
    * \return The Hero's Damage bonus per Level
    */
    int getDmgPerLvl() const;
    /**
    * \return The Hero's Cooldown Multiplier per Level 
    */
    double getCdmPerLvl() const;
    /**
    * \return The Hero's current level. 
    */
    int getLevel() const;
    /**
    * \return The Hero's Defense Bonus Multiplier. 
    */
    int getDefPerLvl() const;
    /**
    * \return The Hero's Defense Bonus Multiplier. 
    */
    int getLightRadius() const;
    /**
    * \return The Hero's Defense Bonus Multiplier. 
    */
    int getLRPerLvl() const;
    /// This method is for attack a Monster with the Hero
    void fightTilDeath(Monster&);
    /**
    * \return The Hero's maximum Health Points. 
    */
    int getMaxHealthPoints() const;
    /// This method is for set the lightradius
    void setLightRadius(int lr_);
    /// This method is doing the attack and levelup.
    void Fight(Monster& monster/**< [in] This is the monster*/,Hero& defend,/**< [in] This is the  Hero */bool HeroAttack/**< [in] Is the hero attacking? */);

    ~Hero(){
    };
};
#endif //Hero_H