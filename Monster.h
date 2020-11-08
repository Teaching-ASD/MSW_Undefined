/**
 * \class Monster
 *
 * \brief Monster class
 *
 * This is a Monster class. This contains the hp, damage, cooldown and XP of the Monster. 
 *
 * \author LeviG9901, 97Vix, b3nc301
 * 
 * \version 2.0
 *
 * \date 2020.10.18. 16:45
 *
 * Created on: 2020.10.16. 18:00
*/
#pragma once
#ifndef MONSTER_H
#define MONSTER_H
#include "Character.h"
#include <math.h>
#include "JSON.h"

class Monster : public Character
{
public:
    /// This is a constructor for Monster
    Monster(const std::string &name_ /**< [in] The Monster's name */, int hp_ /**< [in] The Monster's health */,int damage_ /**< [in] The Monster's damage */,double cd_ /**< [in] The Monster's attackcooldown */);
    /// This is a simple getter for getting the Monster's name.

    /// This method is for parsing the json files. It gets the filename and passes to the json parser. 
    static Monster parse(std::string fname /**< [in] Name of the file */);

    ~Monster(){};
};
#endif //MONSTER_H