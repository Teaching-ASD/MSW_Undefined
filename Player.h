/**
 * \class Player
 *
 * \brief Player class
 *
 * This is a Player class. This contains the maximum and current hp, current damage, current cooldown and XP of the Player. 
 *
 * \author 97Vix
 * 
 * \version 1.0
 *
 * \date 2020.10.16. 18:00
 *
 * Created on: 2020.10.16. 18:00
*/
#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Hero.h"
#include <math.h>

class Player : public Hero
{
private:

int maxHP;
int CurHP;
int CurDMG;
double CurCD;
int XP=0;
std::string stringvar;

public:
/// This is a constructor for Player
Player(const std::string&/**< [in] The Player's name */,int/**< [in] The Player's health */,const int/**< [in] The Player's damage */,const double/**< [in] The Player's attackcooldown */);
/// This method is for parsing the json files. It reads in the file totally and finds: name, hp, damage, attackcooldown. And then it returns an object. There is an exception if it can't find the file. 
/**
 * \exception std::invalid_argument file cannot opened
*/
static Player parseUnitPlayer(std::string fname /**< [in] Name of the file */);
/**
 * \return The Player's current damage
*/
int getCurDMG();
/**
 * \return The Player's current HP
*/
int getCurHP();
/// This method is increasing the xp with the value of the damage
void addXP();
/// This method is doing the levelup.It is changing the value of the maxhp and current hp, dmg, cooldown
void levelUp();
/// This method is decreasing the current hp with the value of the damage
void ChangeCurHp(int); 
/**
 * \return The Player's current cooldown
*/
double getCurCD();
/// This method is doing the attack and levelup.
void Fight(Player* attack/**< [in] This is the attacking player*/,Player* defend/**< [in] This is the defending player */);
/// This method is for the Heroes attacking eachother. It contains the cooldown logic as well. The first two round both of the Heroes attack, but if one of them dies, it just quits from a while loop and endGame() will be called. If noone dies in the first round, then it continues to run in the else statement and there is 4 different cases. First it checks if the first Hero has lower cooldown, then it reduces the second Hero's cooldown with the first Hero's cooldown, and first Hero attacks second Hero. After that the second Hero's cooldown will remain in reduced state and the first Hero will get its original cooldown again. There is another if statement if the second Hero has lower cooldown. It does the same thing as the first one. And then it checks if both of them has the same cooldown, but it is not zero, and it will change both Hero's cooldown to Zero. And the last if statement for the case when both Hero has zero cooldown. The first Hero will start the attack, and there is an if statement for if the second Hero dies while first Hero attacked and second Hero has 0 hp, this if statement will do a continue, which will break out, and the engGame() will be called. If the second Hero doesn't die while the first Hero attacking the second Hero, then it continues to that part, when the second Hero attacks the first Hero, and at the end of the if statement, both of the Hero's cooldown will be the original cooldown again, and the while loop continues until one of them dies.
void Attack(Player* h2_ /**< [in] The enemy Player as parameter */);
/// This method is for checking if one of the two Hero died while attacking eachother, and if one of them died, then it just puts who won as a string in the stringvar variable
/**
 * \return The game is ended
*/
bool endGame(Player* h2_ /**< [in] The enemy Player as parameter */);
/**
 * \return The stringvar variable
*/
std::string getStringvar();
~Player(){
};
};
#endif //Player_H