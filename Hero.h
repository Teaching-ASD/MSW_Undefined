/**
 * \class Hero
 *
 * \brief Hero class
 *
 * This is a Hero class. This contains the name, health, damage, and cooldown of the Hero. The Hero can attack the other Hero, but every Hero has its own attackcooldown, which makes the fight more interesting.
 *
 * \author LeviG9901
 * 
 * \version 1.0
 *
 * \date 2020.10.13. 12:00
 *
 * Created on: 2020.10.13. 12:00
*/
#pragma once
#ifndef HERO_H
#define HERO_H
#include <string>
#include<fstream>

class Hero
{
private:
        const std::string name;     ///< Hero's name
        int hp;                     ///< Hero's health
        const int damage;           ///< Hero's damage
        const double cooldown;      ///< Hero's attackcooldown
        /// This method takes the damage of the enemy Hero, and decreases the Hero's health who took the damage.
        void ChangeHP(int dmg_ /** [in] The enemy Hero's damage paramater */);
        std::string stringvar;      ///< This is a string variable for the iostream. Here stored the endGame() string part. In the main we use this variable to write out who won the fight.
public:
        /// This is a constructor for Hero
        Hero(std::string name_ /** [in] The Hero's name */, int hp_ /** [in] The Hero's health */,int damage_ /** [in] The Hero's damage */,double cd_ /** [in] The Hero's attackcooldown */);
        /// This is a simple getter for getting the Hero's name.
        std::string getName();
        /// This is a simple getter for getting the Hero's damage.
        int getDamage();
        /// This is a simple getter for getting the Hero's health.
        int getHp();
        /// This is a simple getter for getting what stringvar variable contains.
        std::string getStringvar();
        /// This is a simple getter for getting the Hero's attackcooldown.
        double getCooldown();
        /// This method is for checking if one of the two Hero died while attacking eachother, and if one of them died, then it just puts who won as a string in the stringvar variable.
        bool endGame(Hero* h2_ /** [in] The enemy Hero as parameter */);
        /// This method is for the Heroes attacking eachother. It contains the cooldown logic as well. The first two round both of the Heroes attack, but if one of them dies, it just quits from a while loop and endGame() will be called. If noone dies in the first round, then it continues to run in the else statement and there is 4 different cases. First it checks if the first Hero has lower cooldown, then it reduces the second Hero's cooldown with the first Hero's cooldown, and first Hero attacks second Hero. After that the second Hero's cooldown will remain in reduced state and the first Hero will get its original cooldown again. There is another if statement if the second Hero has lower cooldown. It does the same thing as the first one. And then it checks if both of them has the same cooldown, but it is not zero, and it will change both Hero's cooldown to Zero. And the last if statement for the case when both Hero has zero cooldown. The first Hero will start the attack, and there is an if statement for if the second Hero dies while first Hero attacked and second Hero has 0 hp, this if statement will do a continue, which will break out, and the engGame() will be called. If the second Hero doesn't die while the first Hero attacking the second Hero, then it continues to that part, when the second Hero attacks the first Hero, and at the end of the if statement, both of the Hero's cooldown will be the original cooldown again, and the while loop continues until one of them dies.
        void Attack(Hero* h2_ /** [in] The enemy Hero as parameter */);
        ~Hero();
        /// This method is for parsing the json files. It reads in the file totally and finds: name, hp, damage, attackcooldown. And then it returns with this values.
        static Hero parseUnit(std::string fname /** [in] Name of the file */);
};
#endif //HERO_H
