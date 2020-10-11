#include "Player.h"

Player::Player(std::string name,int hp, const int damage):Hero(name,hp,damage){

    this->maxHP=hp;
    this->CurHP=this->maxHP;
    this->CurDMG=damage;


};
void Player::addXP(){

    this->XP += CurDMG;

}

void Player::levelUp(){
    while(this->XP>=100){
        this->XP -=100;

        maxHP = round(maxHP*1.1);
        CurHP = maxHP;
        CurDMG = round(CurDMG*1.1);

    }
    
}

void Player::ChangeCurHp(int dmg){

    CurHP -= dmg;

    if(this->CurHP<0)
    {
        this->CurHP=0;
    }
}

int Player::getCurDMG(){

    return CurDMG;

}

int Player::getCurHP(){

    return CurHP;

}

Player Player::parseUnit(std::string fname){
        std::ifstream file;
        const std::exception e;
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
	    Player object=  Player(hname,hp_,dmg_);
            return object;
}
