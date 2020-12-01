#include <iostream>
#include "Character.h"

Character::Character(const std::string& name_,int hp_,int damage_,double cd_):name(name_), hp(hp_), damage(damage_),cooldown(cd_){
}

std::string Character::getName() const{
    return this->name;
}

int Character::getDamage() const{
    return this->damage;
}

int Character::getHealthPoints() const{
    return this->hp;
}

double Character::getAttackCoolDown() const{
    return this->cooldown;
}

std::string Character::getStringvar() const{
    return this->stringvar;
}

void Character::setHp(int hp_){
    hp = hp_;
}

void Character::setDamage(int dmg){
    damage = dmg;
}

void Character::setCd(double cd){
    cooldown=cd;
}

void Character::ChangeHP(int dmg_){
    this->hp -= dmg_;
    if(this->hp<0)
    {
        this->hp=0;
    }
}


Character Character::parse(std::string fname){
        JSON json;
        json.parseFile(fname);
	    Character object=
        Character(
            json.get<std::string>("name"),
        json.get<int>("health_points"),
        json.get<int>("damage"),
        json.get<int>("attack_cooldown"));
        return object;
}

bool Character::isAlive(){

    if (getHealthPoints() > 0){
            return 1;
    }else{
        return 0;  }

};

Character::~Character(){
};
