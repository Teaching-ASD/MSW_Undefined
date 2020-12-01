#include "Hero.h"
Hero::Hero(const std::string& name,int hp,  int damage, double cd_, const int xpperlvl_, const int hpperlvl_, const int dmgperlvl_, const double cdmperlvl_):Character(name,hp,damage,cd_),xpperlvl(xpperlvl_),hpperlvl(hpperlvl_),dmgperlvl(dmgperlvl_),cdmperlvl(cdmperlvl_){

    this->maxHP=hp;

};
void Hero::addXP(int xp_){

    this->XP += xp_;

}

void Hero::levelUp(){
    while(this->XP>=(level*xpperlvl)){

        level++;
        maxHP = maxHP+hpperlvl;
        this->setHp(maxHP);
        this->setDamage(this->getDamage()+dmgperlvl);
        this->setCd(this->getAttackCoolDown()*cdmperlvl);

    }
}
int Hero::getLevel() const{
    return level;
}

int Hero::getXpPerLvl() const{
    return xpperlvl;
}

int Hero::getHpPerLvl() const{
    return hpperlvl;
}

int Hero::getDmgPerLvl() const{
    return dmgperlvl;
}

double Hero::getCdmPerLvl() const{
    return cdmperlvl;
}

int Hero::getMaxHealthPoints() const{
    return maxHP;
}

Hero Hero::parse(std::string fname){
        JSON json;
        json.parseFile(fname);
	    Hero object=
        Hero(
        json.get<std::string>("name"),
        json.get<int>("health_points"),
        json.get<int>("damage"),
        json.get<double>("attack_cooldown"),
        json.get<int>("experience_per_level"),
        json.get<int>("health_point_bonus_per_level"),
        json.get<int>("damage_bonus_per_level"),
        json.get<double>("cooldown_multiplier_per_level")
        );
        return object;
}


void Hero::Fight(Monster& monster,Hero& hero,bool HeroAttack){
    if(HeroAttack == 1) {
        int OldMonsterHp = monster.getHealthPoints();
        monster.ChangeHP(hero.getDamage());
        hero.addXP(OldMonsterHp-monster.getHealthPoints());
        hero.levelUp();
    }
    else{
        hero.ChangeHP(monster.getDamage());
    }

}

void Hero::fightTilDeath(Monster& monster){
    double cd1 = this->getAttackCoolDown();
    double cd2 = monster.getAttackCoolDown();

    while(monster.getHealthPoints()>0 && this->getHealthPoints()>0)
    {

            if(cd1<cd2)
            {
                cd2 -= cd1;

                //Fight(this,monster);
                Fight(monster,*this,1);
                cd1 = this->getAttackCoolDown();
            }
            else if(cd2 < cd1)
            {
                cd1 -= cd2;
                //Fight(monster,this);
                Fight(monster,*this,0);
                cd2 = monster.getAttackCoolDown();
            }
            else if(cd1==cd2 && (cd1>0||cd2>0))
            {
                cd1 = 0;
                cd2 = 0;
            }
            else if(cd1 == 0 && cd2 ==0)
            {
                //Fight(this,monster);
                Fight(monster,*this,1);
                if(monster.getHealthPoints() <= 0)
                {
                    continue;
                }
                else
                {
                    //Fight(monster,this);
                    Fight(monster,*this,0);
                    cd1 = this->getAttackCoolDown();
                    cd2 = monster.getAttackCoolDown();
                }
            }
       
    }
}



