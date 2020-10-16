#include <iostream>
#include "Hero.h"

Hero::Hero(const std::string& name_,int hp_,const int damage_,const double cd_):name(name_), hp(hp_), damage(damage_),cooldown(cd_)
{

}

std::string Hero::getName()
{
    return this->name;
}

int Hero::getDamage()
{
    return this->damage;
}

int Hero::getHp()
{
    return this->hp;
}

double Hero::getCooldown()
{
    return this->cooldown;
}

/*
void Hero::setHp(int hp_)
{
    hp = hp_;
}
*/

std::string Hero::getStringvar()
{
    return this->stringvar;
}

void Hero::ChangeHP(int dmg_)
{
    this->hp -= dmg_;
    if(this->hp<0)
    {
        this->hp=0;
    }
}


Hero Hero::parseUnitHero(std::string fname){
        std::ifstream file;
        //const std::exception e;
        file.open(fname);
	if(!file.is_open()){throw std::invalid_argument("The file " +fname+ " not exist");}
            std::string hero;
            std::string hname;
            int dmg_;
            int hp_;
            double cd_;
            std::string line;
            //int a = 0;
            while (getline(file,line))
            {
                hero += line;
            }

		hname=hero.substr(
		hero.find(": \"", hero.find("name"))+3,
		(
		(hero.find(',', hero.find("name"))-1)-
		(hero.find(": \"", hero.find("name"))+3)
		));

		hp_=stoi(hero.substr(
		hero.find(":", hero.find("hp"))+1,
		hero.find(',',hero.find("hp"))-hero.find(":",hero.find("hp"))-1
		));

		dmg_=stoi(hero.substr(
		hero.find(":", hero.find("dmg"))+1,
		hero.find(',', hero.find("dmg"))-hero.find(":",hero.find("dmg"))-1
		));

		cd_=stod(hero.substr(
		hero.find(":", hero.find("attackcooldown"))+1,
		hero.find('}', hero.find("attackcooldown"))-hero.find(":",hero.find("attackcooldown"))-1
		));
        file.close();
	    Hero object=  Hero(hname,hp_,dmg_,cd_);
            return object;
}

void Hero::Attack(Hero* h2_){
    int round = 0;
    double cd1 = this->getCooldown();
    double cd2 = h2_->getCooldown();

    while(!endGame(h2_))
    {
        if(round==0)
        {
            h2_->ChangeHP(this->getDamage());
        }
        else if(round==1)
        {
            this->ChangeHP(h2_->getDamage());
        }
        else
        {
            if(cd1<cd2)
            {
                cd2 -= cd1;
                cd1=0;
                h2_->ChangeHP(this->getDamage());
                cd1 = this->getCooldown();
            }
            else if(cd2 < cd1)
            {
                cd1 -= cd2;
                cd2=0;
                this->ChangeHP(h2_->getDamage());
                cd2 = h2_->getCooldown();
            }
            else if(cd1==cd2 && (cd1>0||cd2>0))
            {
                cd1 = 0;
                cd2 = 0;
            }
            else if(cd1 == 0 && cd2 ==0)
            {
                h2_->ChangeHP(this->getDamage());
                if(h2_->getHp() <= 0)
                {
                    continue;
                }
                else
                {
                    this->ChangeHP(h2_->getDamage());
                    cd1 = this->getCooldown();
                    cd2 = h2_->getCooldown();
                }
            }
        }
        round++;
    }
}


bool Hero::endGame(Hero* h2_){
    if(this->getHp()==0){
        this->stringvar =h2_->getName()+ " wins. Remaining HP: " + std::to_string(h2_->getHp());
        return true;
        }
    else if(h2_->getHp()==0){
        this->stringvar= this->getName() + " wins. Remaining HP: " + std::to_string(this->getHp());
        return true;
        }
    else {
        return false;
    }


}

Hero::~Hero()
{

};
