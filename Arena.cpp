#include "Arena.h"


Arena::Arena(){}

void Arena::addHero(Hero hero_){
    this->heroes.push_back(hero_);
}

Arena::~Arena()
{
    this->heroes.clear();
}

void Arena::Attack(){
    int attack=0, attacked=1;
    while(!this->endGame())
    {
        this->heroes[attacked].ChangeHP(this->heroes[attack].getDamage());
        int temp=attack;
        attack=attacked;
        attacked=temp;
    }

}


bool Arena::endGame(){
    if(this->heroes[0].getHp()==0){
        this->stringvar =this->heroes[1].getName()+ " wins. Remaining HP: " + std::to_string(this->heroes[1].getHp());
        return true;
        }
    else if(this->heroes[1].getHp()==0){
        this->stringvar= this->heroes[0].getName() + " wins. Remaining HP: " + std::to_string(this->heroes[0].getHp());
        return true;
        }
    else {
        return false;
    }
}


const std::string Arena::Fight(){
    Attack();
    return this->stringvar;
}


