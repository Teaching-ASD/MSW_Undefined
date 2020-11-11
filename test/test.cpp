#include "../Monster.h"
#include "../Hero.h"
#include "../JSON.h"
#include<gtest/gtest.h>
#include<string>
#include<map>
#include <sstream>
#include<fstream>
#include <algorithm>
#include <iterator>
#include <list>


class JSONTest : public ::testing::Test{
    protected:
    Hero* h1ok = new Hero("Prince Aidan of Khanduras",30,3,1.1,20,5,1,0.9);
    Monster* m1ok = new Monster("Zombie",10,1,2.8);
    std::string h1string = "{    \"name\" : \"Prince Aidan of Khanduras\",    \"base_health_points\" : 30,        \"experience_per_level\" : 20,    \"base_damage\" : 3,    \"base_attack_cooldown\" : 1.1,    \"health_point_bonus_per_level\" : 5,  \"damage_bonus_per_level\" : 1,  \"cooldown_multiplier_per_level\": 0.9}";
    std::string m1string = "{\"lore\" : \"The lowest rank of the undead, zombies befoul much of the wilderness of the Western Kingdoms, as well as the tombs and crypts of the whole of Sanctuary. Zombies serve the darkness blindly and without thought, attacking only with their bare hands. They move slowly, but with relentless determination, seeking to consume the flesh of the living. They are simple-minded and easily outwitted, but in large groups can overwhelm the unwary.\",    \"name\" : \"Zombie\"   ,\"health_points\" : 10     ,\"damage\" : 1, \"attack_cooldown\" : 2.8  ,\"race\" : \"undead\"}";
    std::string expected = "Prince Aidan of Khanduras(1) vs Zombie\nThe hero won.\nPrince Aidan of Khanduras: LVL1\n   HP: 29/30\n  DMG: 3\n  ACD: 1.100000\n";

   std::string getResults(Hero& h1, std::list<Monster> monsters){
               std::string result;
    while (h1.isAlive() && !monsters.empty()) {
                result += h1.getName() + "(" + std::to_string(h1.getLevel()) + ")"
                + " vs "
                + monsters.front().getName()+ "\n";
            h1.fightTilDeath(monsters.front());
            if (!monsters.front().isAlive()) monsters.pop_front();
    }
        result += (h1.isAlive() ? "The hero won.\n" : "The hero died.\n") ;
        result += h1.getName()+ ": LVL" + std::to_string(h1.getLevel()) +"\n"
                  + "   HP: "+std::to_string(h1.getHealthPoints())+"/"+std::to_string(h1.getMaxHealthPoints())+"\n"
                  + "  DMG: "+std::to_string(h1.getDamage())+"\n"
                  + "  ACD: "+std::to_string(h1.getAttackCoolDown())+"\n";
        return result;
    }
    
    void TearDown() override{
        delete h1ok;
        delete m1ok;
    }
};

TEST_F(JSONTest, fileParser){
        
    ASSERT_NO_THROW({
        char fname[]="scenario3.json";
        JSON scenario = JSON::parseFromFile(fname);         
        std::string hero_file;
        std::string monster_file;
        hero_file=scenario.get<std::string>("hero");
        monster_file=scenario.get<std::string>("monsters");
        Hero h1{Hero::parse(hero_file)};
        Monster m1{Monster::parse(monster_file)};
        std::list<Monster> monsters;
        monsters.push_back(Monster::parse(monster_file));
        ASSERT_EQ(h1.getName(),h1ok->getName());
        ASSERT_EQ(h1.getDamage(),h1ok->getDamage());
        ASSERT_EQ(h1.getHealthPoints(),h1ok->getHealthPoints());
        ASSERT_EQ(h1.getAttackCoolDown(), h1ok->getAttackCoolDown());
        ASSERT_EQ(h1.getMaxHealthPoints(), h1ok->getMaxHealthPoints());
        ASSERT_EQ(h1.getDmgPerLvl(), h1ok->getDmgPerLvl());
        ASSERT_EQ(h1.getCdmPerLvl(), h1ok->getCdmPerLvl());
        ASSERT_EQ(h1.getXpPerLvl(), h1ok->getXpPerLvl());    
        ASSERT_EQ(m1.getName(),m1ok->getName());
        ASSERT_EQ(m1.getDamage(),m1ok->getDamage());
        ASSERT_EQ(m1.getHealthPoints(),m1ok->getHealthPoints());
        ASSERT_EQ(m1.getAttackCoolDown(), m1ok->getAttackCoolDown());
        EXPECT_EQ(this->getResults(h1,monsters),expected);
    });
}

TEST_F(JSONTest, fileParserScenario1){
    ASSERT_NO_THROW({
    std::ifstream file;
    file.open("output1.txt");
    std::string line; 
    std::string exp1;
    while (getline(file,line))
        {
            exp1.append(line + "\n");      
        }
    file.close();
    char fname[]="scenario1.json";
    JSON scenario = JSON::parseFromFile(fname);  
    std::string hero_file;
    std::list<std::string> monster_files;
    hero_file=scenario.get<std::string>("hero");
    std::istringstream monsters(scenario.get<std::string>("monsters"));
    std::copy(std::istream_iterator<std::string>(monsters),
        std::istream_iterator<std::string>(),
        std::back_inserter(monster_files));
    Hero hero{Hero::parse(hero_file)};
    std::list<Monster> monsters1;
    for (const auto& monster_file : monster_files){
        monsters1.push_back(Monster::parse(monster_file));
    } 
    EXPECT_EQ(this->getResults(hero,monsters1),exp1);
    });
}

TEST_F(JSONTest, fileParserScenario2){
    ASSERT_NO_THROW({
    std::ifstream file;
    file.open("output2.txt");
    std::string line; 
    std::string exp1;
    while (getline(file,line))
        {
            exp1.append(line + "\n");      
        }
    file.close();
    char fname[]="scenario2.json";
    JSON scenario = JSON::parseFromFile(fname);  
    std::string hero_file;
    std::list<std::string> monster_files;
    hero_file=scenario.get<std::string>("hero");
    std::istringstream monsters(scenario.get<std::string>("monsters"));
    std::copy(std::istream_iterator<std::string>(monsters),
        std::istream_iterator<std::string>(),
        std::back_inserter(monster_files));
    Hero hero{Hero::parse(hero_file)};
    std::list<Monster> monsters1;
    for (const auto& monster_file : monster_files){
        monsters1.push_back(Monster::parse(monster_file));
    } 
    EXPECT_EQ(this->getResults(hero,monsters1),exp1);
    });
}

TEST_F(JSONTest, stringParser){
    std::map<std::string, std::string> adatok;
    ASSERT_NO_THROW({
        JSON json1;
        JSON json2;
        json1.parseString(h1string);
        adatok = json1.getAdatok();
        Hero h1 = Hero(            adatok.at("name"),
        std::stoi(adatok.at("health_points")),
        std::stoi(adatok.at("damage")),
        std::stod(adatok.at("attack_cooldown")),
        std::stod(adatok.at("experience_per_level")),
        std::stod(adatok.at("health_point_bonus_per_level")),
        std::stod(adatok.at("damage_bonus_per_level")),
        std::stod(adatok.at("cooldown_multiplier_per_level")));
        json2.parseString(m1string);
        std::list<Monster> monsters;
        Monster m1 = 
        Monster(
        json2.get<std::string>("name"),std::stoi(json2.get<std::string>("health_points")),std::stoi(json2.get<std::string>("damage")), std::stod(json2.get<std::string>("attack_cooldown")) );
        monsters.push_back(m1);
        ASSERT_EQ(h1.getName(),h1ok->getName());
        ASSERT_EQ(h1.getDamage(),h1ok->getDamage());
        ASSERT_EQ(h1.getHealthPoints(),h1ok->getHealthPoints());
        ASSERT_EQ(h1.getAttackCoolDown(), h1ok->getAttackCoolDown());
        ASSERT_EQ(h1.getMaxHealthPoints(), h1ok->getMaxHealthPoints());
        ASSERT_EQ(h1.getDmgPerLvl(), h1ok->getDmgPerLvl());
        ASSERT_EQ(h1.getCdmPerLvl(), h1ok->getCdmPerLvl());
        ASSERT_EQ(h1.getXpPerLvl(), h1ok->getXpPerLvl());
        ASSERT_EQ(m1.getName(),m1ok->getName());
        ASSERT_EQ(m1.getDamage(),m1ok->getDamage());
        ASSERT_EQ(m1.getHealthPoints(),m1ok->getHealthPoints());
        ASSERT_EQ(m1.getAttackCoolDown(), m1ok->getAttackCoolDown());
       EXPECT_EQ(this->getResults(h1,monsters),expected);
    });

}

TEST_F(JSONTest, istreamParser){
    std::map<std::string, std::string> adatok;
    std::istringstream h1ss(h1string);
    std::istringstream m1ss(m1string);
      ASSERT_NO_THROW({
        JSON json1;
        JSON json2;
        h1ss>>json1;
        adatok = json1.getAdatok();
        Hero h1 = Hero(            adatok.at("name"),
        std::stoi(adatok.at("health_points")),
        std::stoi(adatok.at("damage")),
        std::stod(adatok.at("attack_cooldown")),
        std::stod(adatok.at("experience_per_level")),
        std::stod(adatok.at("health_point_bonus_per_level")),
        std::stod(adatok.at("damage_bonus_per_level")),
        std::stod(adatok.at("cooldown_multiplier_per_level")));
        m1ss>>json2;
        adatok = json2.getAdatok();
        std::list<Monster> monsters;
        Monster m1 = Monster(
            json2.get<std::string>("name"),std::stoi(json2.get<std::string>("health_points")),std::stoi(json2.get<std::string>("damage")), std::stod(json2.get<std::string>("attack_cooldown")) );
        monsters.push_back(m1);
        ASSERT_EQ(h1.getName(),h1ok->getName());
        ASSERT_EQ(h1.getDamage(),h1ok->getDamage());
        ASSERT_EQ(h1.getHealthPoints(),h1ok->getHealthPoints());
        ASSERT_EQ(h1.getAttackCoolDown(), h1ok->getAttackCoolDown());
        ASSERT_EQ(h1.getMaxHealthPoints(), h1ok->getMaxHealthPoints());
        ASSERT_EQ(h1.getDmgPerLvl(), h1ok->getDmgPerLvl());
        ASSERT_EQ(h1.getCdmPerLvl(), h1ok->getCdmPerLvl());
        ASSERT_EQ(h1.getXpPerLvl(), h1ok->getXpPerLvl());
        ASSERT_EQ(m1.getName(),m1ok->getName());
        ASSERT_EQ(m1.getDamage(),m1ok->getDamage());
        ASSERT_EQ(m1.getHealthPoints(),m1ok->getHealthPoints());
        ASSERT_EQ(m1.getAttackCoolDown(), m1ok->getAttackCoolDown());
        EXPECT_EQ(this->getResults(h1,monsters),expected);
    });
}
TEST_F(JSONTest, whiteSpace){
    ASSERT_NO_THROW({
        Monster m1 = Monster(Monster::parse("units/4.json"));
        ASSERT_EQ(m1.getName(),m1ok->getName());
        ASSERT_EQ(m1.getDamage(),m1ok->getDamage());
        ASSERT_EQ(m1.getHealthPoints(),m1ok->getHealthPoints());
        ASSERT_EQ(m1.getAttackCoolDown(), m1ok->getAttackCoolDown());
    });
}
TEST_F(JSONTest, keyOrder){
    ASSERT_NO_THROW({
        Monster m1 = Monster(Monster::parse("units/5.json"));
        ASSERT_EQ(m1.getName(),m1ok->getName());
        ASSERT_EQ(m1.getDamage(),m1ok->getDamage());
        ASSERT_EQ(m1.getHealthPoints(),m1ok->getHealthPoints());
        ASSERT_EQ(m1.getAttackCoolDown(), m1ok->getAttackCoolDown());
    });
}
int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}