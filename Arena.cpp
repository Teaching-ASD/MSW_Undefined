#include "Arena.h"
#include <iostream>

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
        this->stringvar += this->heroes[attack].getName() + " -> " + this->heroes[attacked].getName() + "\n \n";
        int temp=attack;
        attack=attacked;
        attacked=temp;
    }

}


bool Arena::endGame(){
    if(this->heroes[0].getHp()==0){
        addData();
        this->stringvar += this->heroes[0].getName()+ " died. " + this->heroes[1].getName() + " wins. \n";
        return true;
        }
    else if(this->heroes[1].getHp()==0){
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

std::string Arena::parseUnit(std::string fname){
        std::ifstream file;
        file.open(fname);
        std::string hero;
        std::string hname;
        int dmg;
        int hp;
        std::string line;
        int a = 0;
        while (getline(file,line))
        {
            hero += line;
        }
        hname = hero.substr((hero.find(':')+3),((hero.find(',')-4)-hero.find(':')));
        int b = (hero.find("hp")+6);
        a = (hero.find(',', hero.find("hp"))-b);
        hp = stoi(hero.substr(b,a));
        b = (hero.find("dmg")+7);
        a = (hero.find(',', hero.find("hp"))-b);
        dmg = stoi(hero.substr(b,a));
        std::cout << "name: " << hname <<std::endl;
        std::cout << "hp: " << hp <<std::endl;
        std::cout << "dmg: " << dmg <<std::endl;

        return hname;
}
