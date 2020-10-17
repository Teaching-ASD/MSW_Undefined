/**
 * \class Hero
 *
 * \brief Hero class
 *
 * This is a Hero class. This contains the name, health, damage, and cooldown of the Hero. The Hero can attack the other Hero, but every Hero has its own attackcooldown, which makes the fight more interesting.
 *
 * \author 97Vix
 * 
 * \version 2.0
 *
 * \date 2020.10.16. 18:00
 *
 * Created on: 2020.10.16. 18:00
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
        /// This is a constructor for Hero
        Hero(const std::string &name_ /**< [in] The Hero's name */, int hp_ /**< [in] The Hero's health */,const int damage_ /**< [in] The Hero's damage */,const double cd_ /**< [in] The Hero's attackcooldown */);
        /// This is a simple getter for getting the Hero's name.
        /**
         * \return The Hero's name
        */
        std::string getName();
        /**
         * \return The Hero's damage
        */
        int getDamage();
        /**
         * \return The Hero's Hp
        */
        int getHp();
        /**
         * \return The stringvar variable
        */
        std::string getStringvar();
        /**
         * \return The Hero's cooldown
        */
        double getCooldown();
        /// This method is for checking if one of the two Hero died while attacking eachother, and if one of them died, then it just puts who won as a string in the stringvar variable.
        /**
         * \return The game is ended
        */
        bool endGame(Hero* h2_ /**< [in] The enemy Hero as parameter */);
        /// This method is for the Heroes attacking eachother. It contains the cooldown logic as well. The first two round both of the Heroes attack, but if one of them dies, it just quits from a while loop and endGame() will be called. If noone dies in the first round, then it continues to run in the else statement and there is 4 different cases. First it checks if the first Hero has lower cooldown, then it reduces the second Hero's cooldown with the first Hero's cooldown, and first Hero attacks second Hero. After that the second Hero's cooldown will remain in reduced state and the first Hero will get its original cooldown again. There is another if statement if the second Hero has lower cooldown. It does the same thing as the first one. And then it checks if both of them has the same cooldown, but it is not zero, and it will change both Hero's cooldown to Zero. And the last if statement for the case when both Hero has zero cooldown. The first Hero will start the attack, and there is an if statement for if the second Hero dies while first Hero attacked and second Hero has 0 hp, this if statement will do a continue, which will break out, and the engGame() will be called. If the second Hero doesn't die while the first Hero attacking the second Hero, then it continues to that part, when the second Hero attacks the first Hero, and at the end of the if statement, both of the Hero's cooldown will be the original cooldown again, and the while loop continues until one of them dies.
        void Attack(Hero* h2_ /**< [in] The enemy Hero as parameter */);
        /// This method is for parsing the json files. It reads in the file totally and finds: name, hp, damage, attackcooldown. And then it returns an object. There is an exception if it can't find the file. 
        /**
         * \exception std::invalid_argument file cannot opened
        */
        static Hero parseUnitHero(std::string fname /**< [in] Name of the file */);
        ~Hero();
};
#endif //HERO_H
