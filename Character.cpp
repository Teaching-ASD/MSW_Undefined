#include <iostream>
#include "Character.h"

Character::Character(const std::string& name_,int hp_,int damage_,double cd_):name(name_), hp(hp_), damage(damage_),cooldown(cd_)
{

}

std::string Character::getName()
{
    return this->name;
}

int Character::getDamage()
{
    return this->damage;
}

int Character::getHealthPoints()
{
    return this->hp;
}

const double Character::getAttackCoolDown()
{
    return this->cooldown;
}
std::string Character::getStringvar()
{
    return this->stringvar;
}

void Character::setHp(int hp_)
{
    hp = hp_;
}
void Character::setDamage(int dmg){
    damage = dmg;
}
void Character::setCd(double cd){
    cooldown=cd;
}

void Character::ChangeHP(int dmg_)
{
    this->hp -= dmg_;
    if(this->hp<0)
    {
        this->hp=0;
    }
}


Character Character::parse(std::string fname){
        JSON* json = new JSON();
        std::map<std::string,std::string> adatok = json->parseFile(fname);
	    Character object=
        Character(
            adatok.at("name"),
        std::stoi(adatok.at("health_points")),
        std::stoi(adatok.at("damage")),
        std::stod(adatok.at("attack_cooldown"))
        );
        delete json;
        return object;
}

const bool Character::isAlive(){

    if (getHealthPoints() > 0){
            return 1;
    }else{
        return 0;  }

};

Character::~Character()
{

};
