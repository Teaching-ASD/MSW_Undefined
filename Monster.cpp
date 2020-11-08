#include "Monster.h"

Monster::Monster(const std::string &name_, int hp_ ,int damage_,double cd_):Character(name_,hp_,damage_,cd_){
};
    

Monster Monster::parse(std::string fname){
        JSON json;
        std::map<std::string,std::string> adatok = json.parseFile(fname);
	    Monster object=
        Monster(
        adatok.at("name"),
        std::stoi(adatok.at("health_points")),
        std::stoi(adatok.at("damage")),
        std::stod(adatok.at("attack_cooldown"))
        );
        return object;

}