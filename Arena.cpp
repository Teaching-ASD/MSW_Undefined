#include "Arena.h"

Arena::Arena(Hero* hero1,Hero* hero2)
{
    heroes.push_back(hero1);
    heroes.push_back(hero2);

}

const bool Arena::getEnd(){

    if(heroes[0]->getHp() && heroes[0]->getHp() > 0 ){
        return true;
    }else{return false; }

}

const std::string Arena::getData(std::string gyoztes_){

    for(unsigned int x=0;x<this->heroes.size();x++){
        gyoztes_ +=  this->heroes[x]->getName() + ":  HP: " + std::to_string(this->heroes[x]->getHp()) + " DMG: " + std::to_string(this->heroes[x]->getDamage()) + "\n\n";
    }
    return gyoztes_ ;
};

std::string Arena::Attack(){
bool a = 0;
bool b = 1;
std::string gyoztes;
gyoztes=getData(gyoztes);
while(this->getEnd()){
    heroes[b]->setHp(heroes[b]->getHp()-heroes[a]->getDamage());
    if(this->heroes[b]->getHp()<0){this->heroes[b]->setHp(0);}
    gyoztes += heroes[a]->getName()+ " -> " + heroes[b]->getName()+"\n\n";
    if(a == 0) {a = 1;b = 0;}
    else{a = 0;b = 1;}
    gyoztes=getData(gyoztes);
}
gyoztes += heroes[a]->getName() + " died." +  heroes[b]->getName() + " wins.";
return gyoztes;
}

Arena::~Arena()
{
    heroes.clear();
}
