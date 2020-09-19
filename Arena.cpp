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
        this->heroes[attacked].setHp(this->heroes[attacked].getHp()-this->heroes[attack].getDamage());
        this->stringvar += this->heroes[attack].getName() + " -> " + this->heroes[attacked].getName() + "\n \n";
        int temp=attack;
        attack=attacked;
        attacked=temp;
    }

}


bool Arena::endGame(){
    if(this->heroes[0].getHp()<=0){
        this->heroes[0].setHp(0);
        addData();
        this->stringvar += this->heroes[0].getName()+ " died. " + this->heroes[1].getName() + " wins. \n";
        return true;
        }
    else if(this->heroes[1].getHp()<=0){
        this->heroes[1].setHp(0);
        addData();
        this->stringvar += this->heroes[1].getName()+ " died. " + this->heroes[0].getName() + " wins. \n";
        return true;
        }
    else {
        addData();
        return false;
    }
}

void Arena::addData(){
    for(unsigned int x=0;x<this->heroes.size();x++){
        this->stringvar +=  this->heroes[x].getName() + ":  HP: " + std::to_string(this->heroes[x].getHp()) + " DMG: " + std::to_string(this->heroes[x].getDamage()) + "\n\n";
    }
};

const std::string Arena::Fight(){
    Attack();
    return this->stringvar;
}
