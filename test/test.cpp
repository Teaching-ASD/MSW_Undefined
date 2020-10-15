#include "../Arena.h"
#include "../Hero.h"
#include "../Json.h"
#include<gtest/gtest.h>
#include<string>
#include<map>
#include <sstream>
#include<fstream>


class JsonTest : public ::testing::Test{
    protected:
    Arena* Fight = new Arena();
    Hero* hero1ok = new Hero("Bence",800,110);
    Hero* hero2ok = new Hero("Kalman",300,90);
    std::string hero1string = "{\"name\":  \"Bence\",  \"hp\": 800,  \"dmg\": 110}";
    std::string hero2string = "{\"name\":  \"Kalman\",  \"hp\": 300,  \"dmg\": 90}";
    std::string expected = "Bence wins. Remaining HP: 620";
    void TearDown() override{
        delete Fight;
        delete hero1ok;
        delete hero2ok;
    }
};

TEST_F(JsonTest, fileParser){
    ASSERT_NO_THROW({
        Hero* hero1 = new Hero(Hero::parseUnit("units/1.json"));
        Hero* hero2 = new Hero(Hero::parseUnit("units/2.json"));
        ASSERT_EQ(hero1->getName(),hero1ok->getName());
        ASSERT_EQ(hero1->getDamage(),hero1ok->getDamage());
        ASSERT_EQ(hero1->getHp(),hero1ok->getHp());
        ASSERT_EQ(hero2->getName(),hero2ok->getName());
        ASSERT_EQ(hero2->getDamage(),hero2ok->getDamage());
        ASSERT_EQ(hero2->getHp(),hero2ok->getHp());
        Fight->addHero(*hero1);
        Fight->addHero(*hero2);
        EXPECT_EQ(Fight->Fight(),expected);
        delete hero1;
        delete hero2;
        delete Fight;
    });
}
TEST_F(JsonTest, fileParserAll){
    std::ifstream file;
    file.open("good.txt");
    std::string line;
    ASSERT_NO_THROW({
        for (int i=1;i<=3;i++){
            for(int j=1;j<=3;j++){
                if(i!=j){
                    Arena* Fight = new Arena();
                    Hero* hero1 = new Hero(Hero::parseUnit("units/" +std::to_string(i)+".json"));
                    Hero* hero2 = new Hero(Hero::parseUnit("units/" +std::to_string(j)+".json"));
                    Fight->addHero(*hero1);
                    Fight->addHero(*hero2);
                    getline(file,line);
                    EXPECT_EQ(Fight->Fight(),line);
                    delete hero1;
                    delete hero2;
                    delete Fight;
                }
            }
        }
    });
    file.close();
}
TEST_F(JsonTest, stringParser){
    Json* json1 = new Json();
    Json* json2 = new Json();
    std::map<std::string, std::string> adatok;
    ASSERT_NO_THROW({
        json1->parseString(hero1string);
        adatok = json1->getAdatok();
        Hero* hero1 = new Hero(adatok.at("name"),std::stoi(adatok.at("hp")),std::stoi(adatok.at("dmg")));
        json2->parseString(hero2string);
        adatok = json2->getAdatok();
        Hero* hero2 = new Hero(adatok.at("name"),std::stoi(adatok.at("hp")),std::stoi(adatok.at("dmg")));
        ASSERT_EQ(hero1->getName(),hero1ok->getName());
        ASSERT_EQ(hero1->getDamage(),hero1ok->getDamage());
        ASSERT_EQ(hero1->getHp(),hero1ok->getHp());
        ASSERT_EQ(hero2->getName(),hero2ok->getName());
        ASSERT_EQ(hero2->getDamage(),hero2ok->getDamage());
        ASSERT_EQ(hero2->getHp(),hero2ok->getHp());
        Fight->addHero(*hero1);
        Fight->addHero(*hero2);
        EXPECT_EQ(Fight->Fight(),expected);
        delete hero1;
        delete hero2; 
    });
    delete json1;
    delete json2;
    delete Fight;
}
TEST_F(JsonTest, istreamParser){
    Json* json1 = new Json();
    Json* json2 = new Json();
    std::map<std::string, std::string> adatok;
    std::istringstream hero1ss(hero1string);
    std::istringstream hero2ss(hero2string);
    ASSERT_NO_THROW({
        hero1ss>>*json1;
        adatok = json1->getAdatok();
        Hero* hero1 = new Hero(adatok.at("name"),std::stoi(adatok.at("hp")),std::stoi(adatok.at("dmg")));
        hero2ss>>*json2;
        adatok = json2->getAdatok();
        Hero* hero2 = new Hero(adatok.at("name"),std::stoi(adatok.at("hp")),std::stoi(adatok.at("dmg")));
        ASSERT_EQ(hero1->getName(),hero1ok->getName());
        ASSERT_EQ(hero1->getDamage(),hero1ok->getDamage());
        ASSERT_EQ(hero1->getHp(),hero1ok->getHp());
        ASSERT_EQ(hero2->getName(),hero2ok->getName());
        ASSERT_EQ(hero2->getDamage(),hero2ok->getDamage());
        ASSERT_EQ(hero2->getHp(),hero2ok->getHp());
        Fight->addHero(*hero1);
        Fight->addHero(*hero2);
        EXPECT_EQ(Fight->Fight(),expected);
        delete hero1;
        delete hero2; 
    });
    delete json1;
    delete json2;
    delete Fight;
}
int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}