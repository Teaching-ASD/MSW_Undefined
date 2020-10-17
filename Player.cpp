#include "Player.h"

Player::Player(const std::string& name,int hp, const int damage,const double cd_):Hero(name,hp,damage,cd_){

    this->maxHP=hp;
    this->CurHP=this->maxHP;
    this->CurDMG=damage;
    this->CurCD=cd_;


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
        CurCD = CurCD*0.9;
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
double Player::getCurCD(){

    return CurCD;

}
Player Player::parseUnitPlayer(std::string fname){
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
      
	    Player object =  Player(hname,hp_,dmg_,cd_);
            return object;
}
void Player::Fight(Player* attack,Player* defend){

    defend->ChangeCurHp(attack->getCurDMG());
    attack->addXP();
    attack->levelUp();
    defend->levelUp();

}
void Player::Attack(Player* h2_){
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

std::string Player::getStringvar()
{
    return this->stringvar;
}

bool Player::endGame(Player* h2_){
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

