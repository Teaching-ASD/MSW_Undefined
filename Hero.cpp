#include "Hero.h"

Hero::Hero(std::string name_,int hp_,int damage_):name(name_), hp(hp_), damage(damage_)
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

/*
void Hero::setHp(int hp_)
{
    hp = hp_;
}
*/

void Hero::ChangeHP(int dmg_)
{
    this->hp -= dmg_;
    if(this->hp<0)
    {
        this->hp=0;
    }
}

Hero::~Hero()
{

};

Hero Hero::parseUnit(std::string fname){
        std::ifstream file;
        file.open(fname);
        std::string hero;
        std::string hname;
        int dmg_;
        int hp_;
        std::string line;
        int a = 0;
        while (getline(file,line))
        {
            hero += line;
        }
        hname = hero.substr((hero.find(':')+3),((hero.find(',')-4)-hero.find(':')));
        int b = (hero.find("hp")+6);
        a = (hero.find(',', hero.find("hp"))-b);
        hp_ = stoi(hero.substr(b,a));
        b = (hero.find("dmg")+7);
        a = (hero.find(',', hero.find("hp"))-b);
        dmg_ = stoi(hero.substr(b,a));

        Hero object=  Hero(hname,hp_,dmg_);
        return object;
}