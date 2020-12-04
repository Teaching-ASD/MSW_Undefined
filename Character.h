/**
 * \class Character
 *
 * \brief Character class
 *
 * This is a Character class. This contains the name, health, damage, and cooldown of the Character. The Character can attack the other Character, but every Character has its own attackcooldown, which makes the fight more interesting.
 *
 * \author LeviG9901, 97Vix, b3nc301
 * 
 * \version 2.2
 *
 * \date 2020.11.08 12:00
 *
 * Created on: 2020.10.16. 18:00
*/
#pragma once
#ifndef Character_H
#define Character_H
#include <string>
#include <iostream>
#include "JSON.h"

struct Damage{
        int physical = 0;
        int magical = 0;
        Damage(int physical_, int magical_):physical(physical_),magical(magical_){}
        
        Damage& operator+= (int d){
                magical+=d;
                physical+=d;
                return *this;
        }
        
        Damage operator+ (Damage d){
                Damage dmg(d.magical+this->magical,d.physical+this->physical);
                return dmg;
        }
        Damage& operator*= (int d){
                magical*=d;
                physical*=d;
                return *this;
        }
        
};
class Character
{
private:
        const std::string name;
        int hp;
        double cooldown;
        int defense = 0;
        std::string stringvar;
        
public:
        Damage characterDmg;
        void ChangeHP(int/**< [in] The ammount of HP decrease. */);
        void setDamage(int/**< [in] The new damage. */);
        void setCd(double /**< [in] The new CD. */);
        void setHp(int /**< [in] The new HP. */);
        void setDefense(int /**< [in] The new Defense. */);

        /// This is a constructor for Character
        Character(const std::string &name_ /**< [in] The Character's name */, int hp_ /**< [in] The Character's health */,int damage_ /**< [in] The Character's physical damage */,int magical_/**< [in] The Character's magical damage value */,double cd_ /**< [in] The Character's attackcooldown */,int defense_/**< [in] The Character's Defense value */);
        /// This is a simple getter for getting the Character's name.
        /**
         * \return The Character's name
        */
        std::string getName() const;
        /**
         * \return The Character's damage
        */
        int getDamage() const;
        /**
         * \return The Character's Hp
        */
        int getHealthPoints() const;
        /**
         * \return The stringvar variable
        */
        std::string getStringvar() const;
        /**
         * \return The Character's cooldown
        */
        double getAttackCoolDown() const;
        /**
         * \return The Character's cooldown
        */
        int getDefense() const;
        /**
         * \return The Character's physical damage
        */
        int getPhysicalDamage() const;
        /**
         * \return The Character's physical damage
        */
        int getMagicalDamage() const;
        /// This method is for checking if one of the two Character died while attacking eachother, and if one of them died, then it just puts who won as a string in the stringvar variable.
        /**
         * \return The game is ended
        */
        bool endGame(Character* h2_ /**< [in] The enemy Character as parameter */);
        /// This method is for the Characteres attacking eachother. It contains the cooldown logic as well. The first two round both of the Characteres attack, but if one of them dies, it just quits from a while loop and endGame() will be called. If noone dies in the first round, then it continues to run in the else statement and there is 4 different cases. First it checks if the first Character has lower cooldown, then it reduces the second Character's cooldown with the first Character's cooldown, and first Character attacks second Character. After that the second Character's cooldown will remain in reduced state and the first Character will get its original cooldown again. There is another if statement if the second Character has lower cooldown. It does the same thing as the first one. And then it checks if both of them has the same cooldown, but it is not zero, and it will change both Character's cooldown to Zero. And the last if statement for the case when both Character has zero cooldown. The first Character will start the attack, and there is an if statement for if the second Character dies while first Character attacked and second Character has 0 hp, this if statement will do a continue, which will break out, and the engGame() will be called. If the second Character doesn't die while the first Character attacking the second Character, then it continues to that part, when the second Character attacks the first Character, and at the end of the if statement, both of the Character's cooldown will be the original cooldown again, and the while loop continues until one of them dies.
        void Attack(Character* h2_ /**< [in] The enemy Character as parameter */);
        /// This method is for parsing the json files. It gets the filename and passes to the json parser. 
        /**
         * \return A Character object with the datas.
         */
        static Character parse(std::string fname /**< [in] Name of the file */);

        /// This method is for check the character is alive
        /**
         * \return The caracter is alive or not
         */
        bool isAlive();

        ~Character();
};
#endif //Character_H
