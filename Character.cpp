
#include "Character.h"


Character::Character(const std::string& name_,int hp_,int damage_,int magical_,double cd_,int defense_):name(name_), hp(hp_), cooldown(cd_),defense(defense_), characterDmg(Damage(damage_,magical_)){
}

std::string Character::getName() const{
    return this->name;
}

int Character::getHealthPoints() const{
    return this->hp;
}

double Character::getAttackCoolDown() const{
    return this->cooldown;
}

int Character::getDefense() const{
    return this->defense;
}

std::string Character::getStringvar() const{
    return this->stringvar;
}

int Character::getPhysicalDamage() const{
    return characterDmg.physical;
}

int Character::getMagicalDamage() const{
    return characterDmg.magical;
}

void Character::setHp(int hp_){
    hp = hp_;
}

void Character::setDamage(int dmg){
    characterDmg.physical = dmg;
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

void Character::setDefense(int defense_){
    defense = defense_;
}


Character Character::parse(std::string fname){
        JSON json;
        json.parseFile(fname);
	    Character object=
        Character(
        json.get<std::string>("name"),
        json.get<int>("health_points"),
        json.get<int>("damage"),
        json.get<int>("magical_damage"),
        json.get<double>("attack_cooldown"),
        json.get<int>("defense")
        );
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
