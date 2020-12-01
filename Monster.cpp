#include "Monster.h"

Monster::Monster(const std::string &name_, int hp_ ,int damage_,double cd_):Character(name_,hp_,damage_,cd_){
};
    

Monster Monster::parse(std::string fname){
        JSON json;
        json.parseFile(fname);
	    Monster object=
        Monster(
        json.get<std::string>("name"),
        json.get<int>("health_points"),
        json.get<int>("damage"),
        json.get<double>("attack_cooldown")
        );
        return object;

}