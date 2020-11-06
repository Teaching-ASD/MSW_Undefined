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

class Hero : public Character
{
private:

int maxHP;
int CurHP;
int CurDMG;
double CurCD;
int XP=0;
std::string stringvar;

public:
/// This is a constructor for Hero
Hero(const std::string&/**< [in] The Hero's name */,int/**< [in] The Hero's health */,const int/**< [in] The Hero's damage */,const double/**< [in] The Hero's attackcooldown */);
/// This method is for parsing the json files. It gets the filename and passes to the json parser. 
static Hero parseUnitHero(std::string fname /**< [in] Name of the file */);
/**
 * \return The Hero's current damage
*/
int getCurDMG();
/**
 * \return The Hero's current HP
*/
int getCurHP();
/// This method is increasing the xp with the value of the damage
void addXP();
/// This method is doing the levelup.It is changing the value of the maxhp and current hp, dmg, cooldown
void levelUp();
/// This method is decreasing the current hp with the value of the damage
void ChangeCurHp(int); 
/**
 * \return The Hero's current cooldown
*/
double getCurCD();
/// This method is doing the attack and levelup.
void Fight(Hero* attack/**< [in] This is the attacking Hero*/,Hero* defend/**< [in] This is the defending Hero */);
/// This method is for the Characteres attacking eachother. It contains the cooldown logic as well. The first two round both of the Characteres attack, but if one of them dies, it just quits from a while loop and endGame() will be called. If noone dies in the first round, then it continues to run in the else statement and there is 4 different cases. First it checks if the first Character has lower cooldown, then it reduces the second Character's cooldown with the first Character's cooldown, and first Character attacks second Character. After that the second Character's cooldown will remain in reduced state and the first Character will get its original cooldown again. There is another if statement if the second Character has lower cooldown. It does the same thing as the first one. And then it checks if both of them has the same cooldown, but it is not zero, and it will change both Character's cooldown to Zero. And the last if statement for the case when both Character has zero cooldown. The first Character will start the attack, and there is an if statement for if the second Character dies while first Character attacked and second Character has 0 hp, this if statement will do a continue, which will break out, and the engGame() will be called. If the second Character doesn't die while the first Character attacking the second Character, then it continues to that part, when the second Character attacks the first Character, and at the end of the if statement, both of the Character's cooldown will be the original cooldown again, and the while loop continues until one of them dies.
void Attack(Hero* h2_ /**< [in] The enemy Hero as parameter */);
/// This method is for checking if one of the two Character died while attacking eachother, and if one of them died, then it just puts who won as a string in the stringvar variable
/**
 * \return The game is ended
*/
bool endGame(Hero* h2_ /**< [in] The enemy Hero as parameter */);
/**
 * \return The stringvar variable
*/
std::string getStringvar();
~Hero(){
};
};
#endif //Hero_H