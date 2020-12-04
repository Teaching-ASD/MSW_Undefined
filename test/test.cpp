#include "../Monster.h"
#include "../Hero.h"
#include "../JSON.h"
#include "../Game.h"
#include "../Map.h"
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
    Hero* h1ok = new Hero("Prince Aidan of Khanduras",30,1,1,1.1,20,5,1,0.9,1,0.1);
    Monster* m1ok = new Monster("Zombie",10,1,1,2.8,1);
    std::string h1string = "{    \"name\" : \"Prince Aidan of Khanduras\", \"defense\": 1,\"defense_bonus_per_level\": 0.1,     \"base_health_points\" : 30,        \"experience_per_level\" : 20, \"magical_damage\":1,   \"damage\" : 1,    \"base_attack_cooldown\" : 1.1,    \"health_point_bonus_per_level\" : 5,  \"damage_bonus_per_level\" : 1,  \"cooldown_multiplier_per_level\": 0.9}";
    std::string m1string = "{\"lore\" : \"The lowest rank of the undead, zombies befoul much of the wilderness of the Western Kingdoms, as well as the tombs and crypts of the whole of Sanctuary. Zombies serve the darkness blindly and without thought, attacking only with their bare hands. They move slowly, but with relentless determination, seeking to consume the flesh of the living. They are simple-minded and easily outwitted, but in large groups can overwhelm the unwary.\",    \"name\" : \"Zombie\"   ,\"health_points\" : 10     ,\"damage\" : 1, \"magical_damage\":1, \"defense\":1, \"attack_cooldown\" : 2.8  ,\"race\" : \"undead\"}";
    std::string expected = "Prince Aidan of Khanduras(1) vs Zombie\nThe hero won.\nPrince Aidan of Khanduras: LVL1\n   HP: 27/30\n  ACD: 1.100000\n";

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
                 // + "  DMG: "+std::to_string(h1.getDamage())+"\n"
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
        std::list<std::string> monster_files;
        hero_file=scenario.get<std::string>("hero");
        JSON::list monster_file_list=scenario.get<JSON::list>("monsters");
        for(auto monster_file : monster_file_list)
            monster_files.push_back(std::get<std::string>(monster_file));
        Hero h1{Hero::parse(hero_file)};
        Monster m1{Monster::parse(monster_files.back())};
        std::list<Monster> monsters;
        monsters.push_back(Monster::parse(monster_files.back()));
        ASSERT_EQ(h1.getName(),h1ok->getName());
        ASSERT_EQ(h1.getHealthPoints(),h1ok->getHealthPoints());
        ASSERT_EQ(h1.getAttackCoolDown(), h1ok->getAttackCoolDown());
        ASSERT_EQ(h1.getMaxHealthPoints(), h1ok->getMaxHealthPoints());
        ASSERT_EQ(h1.getDmgPerLvl(), h1ok->getDmgPerLvl());
        ASSERT_EQ(h1.getCdmPerLvl(), h1ok->getCdmPerLvl());
        ASSERT_EQ(h1.getXpPerLvl(), h1ok->getXpPerLvl());    
        ASSERT_EQ(m1.getName(),m1ok->getName());
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
    JSON::list monster_file_list=scenario.get<JSON::list>("monsters");
    for(auto monster_file : monster_file_list)
        monster_files.push_back(std::get<std::string>(monster_file));
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
    JSON::list monster_file_list=scenario.get<JSON::list>("monsters");
    for(auto monster_file : monster_file_list)
        monster_files.push_back(std::get<std::string>(monster_file));
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
        Hero h1 =         Hero(
        json1.get<std::string>("name"),
        json1.get<int>("health_points"),
        json1.get<int>("damage"),
        json1.get<int>("magical_damage"),
        json1.get<double>("attack_cooldown"),
        json1.get<int>("experience_per_level"),
        json1.get<int>("health_point_bonus_per_level"),
        json1.get<int>("damage_bonus_per_level"),
        json1.get<double>("cooldown_multiplier_per_level"),
        json1.get<int>("defense"),
        json1.get<double>("defense_bonus_per_level")
        );
        json2.parseString(m1string);
        std::list<Monster> monsters;
        Monster m1 = 
                Monster(
        json2.get<std::string>("name"),
        json2.get<int>("health_points"),
        json2.get<int>("damage"),
        json2.get<int>("magical_damage"),
        json2.get<double>("attack_cooldown"),
        json2.get<int>("defense")
        );
        monsters.push_back(m1);
        ASSERT_EQ(h1.getName(),h1ok->getName());
        ASSERT_EQ(h1.getHealthPoints(),h1ok->getHealthPoints());
        ASSERT_EQ(h1.getAttackCoolDown(), h1ok->getAttackCoolDown());
        ASSERT_EQ(h1.getMaxHealthPoints(), h1ok->getMaxHealthPoints());
        ASSERT_EQ(h1.getDmgPerLvl(), h1ok->getDmgPerLvl());
        ASSERT_EQ(h1.getCdmPerLvl(), h1ok->getCdmPerLvl());
        ASSERT_EQ(h1.getXpPerLvl(), h1ok->getXpPerLvl());
        ASSERT_EQ(m1.getName(),m1ok->getName());
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
        Hero h1 =         Hero(
        json1.get<std::string>("name"),
        json1.get<int>("health_points"),
        json1.get<int>("damage"),
        json1.get<int>("magical_damage"),
        json1.get<double>("attack_cooldown"),
        json1.get<int>("experience_per_level"),
        json1.get<int>("health_point_bonus_per_level"),
        json1.get<int>("damage_bonus_per_level"),
        json1.get<double>("cooldown_multiplier_per_level"),
        json1.get<int>("defense"),
        json1.get<double>("defense_bonus_per_level")
        );
        m1ss>>json2;
        std::list<Monster> monsters;
        Monster m1 = 
                Monster(
        json2.get<std::string>("name"),
        json2.get<int>("health_points"),
        json2.get<int>("damage"),
        json2.get<int>("magical_damage"),
        json2.get<double>("attack_cooldown"),
        json2.get<int>("defense")
        );
        monsters.push_back(m1);
        ASSERT_EQ(h1.getName(),h1ok->getName());
        //ASSERT_EQ(h1.getDamage(),h1ok->getDamage());
        ASSERT_EQ(h1.getHealthPoints(),h1ok->getHealthPoints());
        ASSERT_EQ(h1.getAttackCoolDown(), h1ok->getAttackCoolDown());
        ASSERT_EQ(h1.getMaxHealthPoints(), h1ok->getMaxHealthPoints());
        ASSERT_EQ(h1.getDmgPerLvl(), h1ok->getDmgPerLvl());
        ASSERT_EQ(h1.getCdmPerLvl(), h1ok->getCdmPerLvl());
        ASSERT_EQ(h1.getXpPerLvl(), h1ok->getXpPerLvl());
        ASSERT_EQ(m1.getName(),m1ok->getName());
       // ASSERT_EQ(m1.getDamage(),m1ok->getDamage());
        ASSERT_EQ(m1.getHealthPoints(),m1ok->getHealthPoints());
        ASSERT_EQ(m1.getAttackCoolDown(), m1ok->getAttackCoolDown());
     //   EXPECT_EQ(this->getResults(h1,monsters),expected);
    });
}
TEST_F(JSONTest, whiteSpace){
    ASSERT_NO_THROW({
        Monster m1 = Monster(Monster::parse("units/4.json"));
        ASSERT_EQ(m1.getName(),m1ok->getName());
       // ASSERT_EQ(m1.getDamage(),m1ok->getDamage());
        ASSERT_EQ(m1.getHealthPoints(),m1ok->getHealthPoints());
        ASSERT_EQ(m1.getAttackCoolDown(), m1ok->getAttackCoolDown());
    });
}
TEST_F(JSONTest, keyOrder){
    ASSERT_NO_THROW({
        Monster m1 = Monster(Monster::parse("units/5.json"));
        ASSERT_EQ(m1.getName(),m1ok->getName());
        ASSERT_EQ(m1.getHealthPoints(),m1ok->getHealthPoints());
        ASSERT_EQ(m1.getAttackCoolDown(), m1ok->getAttackCoolDown());
    });
}

TEST(GameTest,gameStart){
    ASSERT_NO_THROW({
          char fname[]="scenario1.json";
    JSON scenario = JSON::parseFromFile(fname);  
    std::string hero_file;
    std::list<std::string> monster_files;
    hero_file=scenario.get<std::string>("hero");
    JSON::list monster_file_list=scenario.get<JSON::list>("monsters");
    for(auto monster_file : monster_file_list)
        monster_files.push_back(std::get<std::string>(monster_file));
    Hero hero{Hero::parse(hero_file)};
    std::list<Monster> monsters1;
    for (const auto& monster_file : monster_files){
        monsters1.push_back(Monster::parse(monster_file));
    } 
    Map map("map1.txt");
      Game game;
      game.setMap(map);
    freopen("commands.txt","r",stdin);
      game.setChInMap(monsters1,hero);
    freopen("commandsnavigate.txt","r",stdin);
      game.run();
    });
}
TEST(GameTest, exceptionTets){
         std::string mapfile = "map1.txt";
            Game game(mapfile);
        char fname[]="scenario1.json";
    JSON scenario = JSON::parseFromFile(fname);  
    std::string hero_file;
    std::list<std::string> monster_files;
    hero_file=scenario.get<std::string>("hero");
    JSON::list monster_file_list=scenario.get<JSON::list>("monsters");
    for(auto monster_file : monster_file_list)
        monster_files.push_back(std::get<std::string>(monster_file));
    Hero hero{Hero::parse(hero_file)};
    std::list<Monster> monsters1;
    for (const auto& monster_file : monster_files){
        monsters1.push_back(Monster::parse(monster_file));
    } 
    ASSERT_THROW({

        game.putHero(hero,1,1);
        game.putHero(hero,2,1);
    }, Game::AlreadyHasHeroException);
    ASSERT_THROW({
        game.putHero(hero,0,0);
    },Game::OccupiedException);
    ASSERT_THROW({
        game.putMonster(monsters1.front(),1,1);
        Map map2("map2.txt");
        game.setMap(map2);
    },Game::AlreadyHasUnitsException);
    ASSERT_THROW({
        Game game2;
        game2.run();
    },Game::NotInitializedException);
    ASSERT_THROW({
        Map map2("map2.txt");
        map2.get(100,100);
    },Map::WrongIndexException);
}
int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}