#include "Monster.h"

Monster::Monster(const std::string &name_, int hp_ , int damage_, int magical_,double cd_,int defense_):Character(name_,hp_,damage_,magical_,cd_,defense_){
};
    

Monster Monster::parse(std::string fname){
        JSON json;
        json.parseFile(fname);
	    Monster object=
        Monster(
        json.get<std::string>("name"),
        json.get<int>("health_points"),
        json.get<int>("damage"),
        json.get<int>("magical_damage"),
        json.get<double>("attack_cooldown"),
        json.get<int>("defense")
        );
        return object;

}