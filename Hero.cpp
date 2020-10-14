#include "Hero.h"

Hero::Hero(const std::string& name_,int hp_,const int damage_):name(name_), hp(hp_), damage(damage_)
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

int Hero::getCurHP()
{
    return this->hp;
}

/*
void Hero::setHp(int hp_)
{
    hp = hp_;
}
*/
/*
void Hero::ChangeHP(int dmg_)
{
    this->hp -= dmg_;
    if(this->hp<0)
    {
        this->hp=0;
    }
}
*/

Hero Hero::parseUnitHero(std::string fname){
        std::ifstream file;
        //const std::exception e;
        file.open(fname);
	if(!file.is_open()){throw std::invalid_argument("The file " +fname+ " not exist");}
            std::string hero;
            std::string hname;
            int dmg_;
            int hp_;
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
		hero.find('}', hero.find("dmg"))-hero.find(":",hero.find("dmg"))-1
		));
	    Hero object =  Hero(hname,hp_,dmg_);
            return object;
}

Hero::~Hero()
{

};


