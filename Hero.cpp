#include "Hero.h"

Hero::Hero(const std::string& name,int hp, const int damage,const double cd_, const int xpperlvl_, const int hpperlvl_, const int dmgperlvl_, const double cdmperlvl_):Character(name,hp,damage,cd_),xpperlvl(xpperlvl_),hpperlvl(hpperlvl_),dmgperlvl(dmgperlvl_),cdmperlvl(cdmperlvl_){

    this->maxHP=hp;
    this->CurHP=this->maxHP;
    this->CurDMG=damage;
    this->CurCD=cd_;

};
void Hero::addXP(){

    this->XP += CurDMG;

}

void Hero::levelUp(){
    while(this->XP>=100){
        this->XP -=100;
        
        maxHP = round(maxHP*1.1);
        CurHP = maxHP;
        CurDMG = round(CurDMG*1.1);
        CurCD = CurCD*0.9;
    }
    
}

void Hero::ChangeCurHp(int dmg){

    CurHP -= dmg;

    if(this->CurHP<0)
    {
        this->CurHP=0;
    }
}

int Hero::getCurDMG(){

    return CurDMG;

}

int Hero::getCurHP(){

    return CurHP;

}
double Hero::getCurCD(){

    return CurCD;

}

const int Hero::getXpPerLvl(){
    return xpperlvl;
}

const int Hero::getHpPerLvl(){
    return hpperlvl;
}

const int Hero::getDmgPerLvl(){
    return dmgperlvl;
}

const double Hero::getCdmPerLvl(){
    return cdmperlvl;
}

Hero Hero::parse(std::string fname){
        JSON* json = new JSON();
        std::map<std::string,std::string> adatok = json->parseFile(fname);
	    Hero object=
        Hero(
            adatok.at("name"),
        std::stoi(adatok.at("health_points")),
        std::stoi(adatok.at("damage")),
        std::stod(adatok.at("attack_cooldown")),
        std::stod(adatok.at("experience_per_level")),
        std::stod(adatok.at("health_point_bonus_per_level")),
        std::stod(adatok.at("damage_bonus_per_level")),
        std::stod(adatok.at("cooldown_multiplier_per_level"))
        );
        delete json;
        return object;
}
/*
void Hero::Fight(Hero* attack,Hero* defend){

    defend->ChangeCurHp(attack->getCurDMG());
    attack->addXP();
    attack->levelUp();
    defend->levelUp();

}
void Hero::Attack(Hero* h2_){
    int round = 0;
    double cd1 = this->getCurCD();
    double cd2 = h2_->getCurCD();

    while(!endGame(h2_))
    {
        if(round==0)
        {
            Fight(this,h2_);
        }
        else if(round==1)
        {
            Fight(h2_,this);
        }
        else
        {
            if(cd1<cd2)
            {
                cd2 -= cd1;

                Fight(this,h2_);
                cd1 = this->getCurCD();
            }
            else if(cd2 < cd1)
            {
                cd1 -= cd2;
                Fight(h2_,this);
                cd2 = h2_->getCurCD();
            }
            else if(cd1==cd2 && (cd1>0||cd2>0))
            {
                cd1 = 0;
                cd2 = 0;
            }
            else if(cd1 == 0 && cd2 ==0)
            {
                Fight(this,h2_);
                if(h2_->getCurHP() <= 0)
                {
                    continue;
                }
                else
                {
                    Fight(h2_,this);
                    cd1 = this->getCurCD();
                    cd2 = h2_->getCurCD();
                }
            }
        }
        round++;
    }
}

std::string Hero::getStringvar()
{
    return this->stringvar;
}

bool Hero::endGame(Hero* h2_){
    if(this->getCurHP()==0){
        this->stringvar =h2_->getName()+ " wins. Remaining HP: " + std::to_string(h2_->getCurHP());
        return true;
        }
    else if(h2_->getCurHP()==0){
        this->stringvar= this->getName() + " wins. Remaining HP: " + std::to_string(this->getCurHP());
        return true;
        }
    else {
        return false;
    }
}
*/

