#include "Hero.h"
#include <iostream>
Hero::Hero(const std::string& name,int hp, int damage_, int magical_,double cd_, const int xpperlvl_, const int hpperlvl_, const int dmgperlvl_, const double cdmperlvl_, int defense_, const double defperlvl_):Character(name,hp,damage_,magical_,cd_,defense_),xpperlvl(xpperlvl_),hpperlvl(hpperlvl_),dmgperlvl(dmgperlvl_),cdmperlvl(cdmperlvl_),defperlvl(defperlvl_){

    this->maxHP=hp;

};
void Hero::addXP(int xp_){

    this->XP += xp_;

}
/*
void Hero::levelUp(){
    while(this->XP>=(level*xpperlvl)){

        level++;
        maxHP = maxHP+hpperlvl;
        this->setHp(maxHP);
        this->setDamage(this->getDamage()+dmgperlvl);
        this->setCd(this->getAttackCoolDown()*cdmperlvl);

    }
}
*/
void Hero::levelUp(){
    while(this->XP>=(level*xpperlvl)){
        level++;
        maxHP = maxHP+hpperlvl;
        this->setHp(maxHP);
        //this->setDamage(this->getDamage()+dmgperlvl);
        this->characterDmg+=dmgperlvl;
        this->setCd(this->getAttackCoolDown()*cdmperlvl);
	    this->setDefense(this->getDefense()+defperlvl);
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

int Hero::getDefPerLvl() const{
    return defperlvl;
}

Hero Hero::parse(std::string fname){
        JSON json;
        json.parseFile(fname);
	    Hero object=
        Hero(
        json.get<std::string>("name"),
        json.get<int>("health_points"),
        json.get<int>("base_damage"),
        json.get<int>("magical_damage"),
        json.get<double>("attack_cooldown"),
        json.get<int>("experience_per_level"),
        json.get<int>("health_point_bonus_per_level"),
        json.get<int>("damage_bonus_per_level"),
        json.get<double>("cooldown_multiplier_per_level"),
        json.get<int>("defense"),
        json.get<double>("defense_bonus_per_level")
        );
        return object;
}

/*
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
*/
void Hero::Fight(Monster& monster,Hero& hero,bool HeroAttack){
    std::cout<<"\n\nBelelépett";
    std::cout<<"\nHős XP/LVL: "<<hero.getXpPerLvl();
    std::cout<<"\nHős neve: "<<hero.getName();
    std::cout<<"\nHős physical damage: "<<hero.getPhysicalDamage();
    std::cout<<"\nHős magical damage: "<<hero.getMagicalDamage();
    std::cout<<"\nHős szintje: "<<hero.getLevel();
    std::cout<<"\nHős hp: "<<hero.getHealthPoints();
    std::cout<<"\nHős attack cooldown: "<<hero.getAttackCoolDown();
    std::cout<<"\nHős defense: "<<hero.getDefense();
    std::cout<<"\nMonster neve: "<<monster.getName();
    std::cout<<"\nMonster élete: "<<monster.getHealthPoints();
    std::cout<<"\nMonster physical damage: "<<monster.getPhysicalDamage();
    std::cout<<"\nMonster magical damage: "<<monster.getMagicalDamage();
    std::cout<<"\nMonster attack cooldown: "<<monster.getAttackCoolDown();
    std::cout<<"\nMonster defense: "<<monster.getDefense();
    std::cout<<"\nHeroAttack== "<<HeroAttack;
    if(HeroAttack == 1) {
        //std::cout<<("\nBelelépett az első ifbe");
        int OldMonsterHp = monster.getHealthPoints();
        if(monster.getDefense()<hero.getPhysicalDamage())//Ha a monster defense kisebb mint a Hero physical damage akkor üti a monstert
        {
            //std::cout<<("\nHa a Defense kisebb mint a Damage");
            monster.ChangeHP((hero.getPhysicalDamage()-monster.getDefense())+hero.getMagicalDamage());
            hero.addXP(OldMonsterHp-monster.getHealthPoints());
            hero.levelUp();
        }
        else if(hero.getMagicalDamage()>0)
        {
            //std::cout<<("\nHa a Defense nagyobb, mint a Damage vagy egyenlő");
            monster.ChangeHP(hero.getMagicalDamage());
            hero.addXP(OldMonsterHp-monster.getHealthPoints());
            hero.levelUp();	
        }
        else
        {
            std::cout<<"\nVégtelen háború";
        }
        
            //monster.ChangeHP(hero.getDamage());
            //hero.addXP(OldMonsterHp-monster.getHealthPoints());
            //hero.levelUp();
    }
    else{
        if(hero.getDefense()<monster.getPhysicalDamage())//Ha a monster defense kisebb mint a Hero physical damage akkor üti a monstert
        {
            std::cout<<("\nHa a HERO Defense kisebb mint a MONSTER Damage");
            std::cout<<"Monster.getMagicalDamage(): " << monster.getMagicalDamage()<<std::endl;
            std::cout<<"Monster.getPhysicalDamage(): " << monster.getPhysicalDamage()<<std::endl;
            hero.ChangeHP((monster.getPhysicalDamage()-hero.getDefense())+monster.getMagicalDamage());
        }
        else if(monster.getMagicalDamage()>0)
        {
            std::cout<<("\nHa a Defense nagyobb, mint a Damage vagy egyenlő");
            std::cout<<"Monster.getMagicalDamage(): " << monster.getMagicalDamage()<<std::endl;
            std::cout<<"Monster.getPhysicalDamage(): " << monster.getPhysicalDamage()<<std::endl;
            hero.ChangeHP(monster.getMagicalDamage());
        }
        else
        {
            std::cout<<"\nLófasz nem történt basszam szájba!"<<std::endl;
            std::cout<<"Monster.getMagicalDamage(): " << monster.getMagicalDamage()<<std::endl;
            std::cout<<"Monster.getPhysicalDamage(): " << monster.getPhysicalDamage()<<std::endl;
        }
        
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



