#include "../Player.h"
#include "../Json.h"
#include<gtest/gtest.h>
#include<string>
#include<map>
#include <sstream>
#include<fstream>


class JsonTest : public ::testing::Test{
    protected:
    Player* p1ok = new Player("Bence",125,50, 1.5);
    Player* p2ok = new Player("Kalman",300,70, 3.5);
    std::string p1string = "{\"name\":  \"Bence\",  \"hp\": 125,  \"dmg\": 50, \"attackcooldown\": 1.5}";
    std::string p2string = "{\"name\":  \"Kalman\",  \"hp\": 300,  \"dmg\": 70, \"attackcooldown\": 3.5}";
    std::string expected = "Bence wins. Remaining HP: 295";
    void TearDown() override{
        delete p1ok;
        delete p2ok;
    }
};

TEST_F(JsonTest, fileParser){
    ASSERT_NO_THROW({
        Player* p1 = new Player(Player::parseUnitPlayer("units/1.json"));
        Player* p2 = new Player(Player::parseUnitPlayer("units/2.json"));
        ASSERT_EQ(p1->getName(),p1ok->getName());
        ASSERT_EQ(p1->getDamage(),p1ok->getDamage());
        ASSERT_EQ(p1->getHp(),p1ok->getHp());
        ASSERT_EQ(p1->getCooldown(), p1ok->getCooldown());
        ASSERT_EQ(p2->getName(),p2ok->getName());
        ASSERT_EQ(p2->getDamage(),p2ok->getDamage());
        ASSERT_EQ(p2->getHp(),p2ok->getHp());
        ASSERT_EQ(p1->getCooldown(), p1ok->getCooldown());
        ASSERT_EQ(p2->getCooldown(), p2ok->getCooldown());
        p1->Attack(p2);
        EXPECT_EQ(p1->getStringvar(),expected);
        delete p1;
        delete p2;
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
                    Player* p1 = new Player(Player::parseUnitPlayer("units/" +std::to_string(i)+".json"));
                    Player* p2 = new Player(Player::parseUnitPlayer("units/" +std::to_string(j)+".json"));
                    p1->Attack(p2);
                    getline(file,line);
                    EXPECT_EQ(p1->getStringvar(),line);
                    delete p1;
                    delete p2;
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
        json1->parseString(p1string);
        adatok = json1->getAdatok();
        Player* p1 = new Player(adatok.at("name"),std::stoi(adatok.at("hp")),std::stoi(adatok.at("dmg")), std::stod(adatok.at("attackcooldown")) );
        json2->parseString(p2string);
        adatok = json2->getAdatok();
        Player* p2 = new Player(adatok.at("name"),std::stoi(adatok.at("hp")),std::stoi(adatok.at("dmg")), std::stod(adatok.at("attackcooldown")) );
        ASSERT_EQ(p1->getName(),p1ok->getName());
        ASSERT_EQ(p1->getDamage(),p1ok->getDamage());
        ASSERT_EQ(p1->getHp(),p1ok->getHp());
        ASSERT_EQ(p1->getCooldown(), p1ok->getCooldown());
        ASSERT_EQ(p2->getName(),p2ok->getName());
        ASSERT_EQ(p2->getDamage(),p2ok->getDamage());
        ASSERT_EQ(p2->getHp(),p2ok->getHp());
        ASSERT_EQ(p2->getCooldown(), p2ok->getCooldown());
        p1->Attack(p2);
        EXPECT_EQ(p1->getStringvar(),expected);
        delete p1;
        delete p2; 
    });
    delete json1;
    delete json2;
}
TEST_F(JsonTest, istreamParser){
    Json* json1 = new Json();
    Json* json2 = new Json();
    std::map<std::string, std::string> adatok;
    std::istringstream p1ss(p1string);
    std::istringstream p2ss(p2string);
    ASSERT_NO_THROW({
        p1ss>>*json1;
        adatok = json1->getAdatok();
        Player* p1 = new Player(adatok.at("name"),std::stoi(adatok.at("hp")),std::stoi(adatok.at("dmg")), std::stod(adatok.at("attackcooldown")));
        p2ss>>*json2;
        adatok = json2->getAdatok();
        Player* p2 = new Player(adatok.at("name"),std::stoi(adatok.at("hp")),std::stoi(adatok.at("dmg")), std::stod(adatok.at("attackcooldown")));
        ASSERT_EQ(p1->getName(),p1ok->getName());
        ASSERT_EQ(p1->getDamage(),p1ok->getDamage());
        ASSERT_EQ(p1->getHp(),p1ok->getHp());
        ASSERT_EQ(p1->getCooldown(), p1ok->getCooldown());
        ASSERT_EQ(p2->getName(),p2ok->getName());
        ASSERT_EQ(p2->getDamage(),p2ok->getDamage());
        ASSERT_EQ(p2->getHp(),p2ok->getHp());
        ASSERT_EQ(p2->getCooldown(), p2ok->getCooldown());
        p1->Attack(p2);
        EXPECT_EQ(p1->getStringvar(),expected);
        delete p1;
        delete p2; 
    });
    delete json1;
    delete json2;
}
TEST_F(JsonTest, whiteSpace){
    ASSERT_NO_THROW({
        Player* p1 = new Player(Player::parseUnitPlayer("units/4.json"));
        Player* p2 = new Player(Player::parseUnitPlayer("units/5.json"));
        ASSERT_EQ(p1->getName(),p1ok->getName());
        ASSERT_EQ(p1->getDamage(),p1ok->getDamage());
        ASSERT_EQ(p1->getHp(),p1ok->getHp());
        ASSERT_EQ(p1->getCooldown(), p1ok->getCooldown());
        ASSERT_EQ(p2->getName(),p2ok->getName());
        ASSERT_EQ(p2->getDamage(),p2ok->getDamage());
        ASSERT_EQ(p2->getHp(),p2ok->getHp());
        ASSERT_EQ(p1->getCooldown(), p1ok->getCooldown());
        ASSERT_EQ(p2->getCooldown(), p2ok->getCooldown());
        p1->Attack(p2);
        EXPECT_EQ(p1->getStringvar(),expected);
        delete p1;
        delete p2;
    });
}
TEST_F(JsonTest, keyOrder){
    ASSERT_NO_THROW({
        Player* p1 = new Player(Player::parseUnitPlayer("units/6.json"));
        Player* p2 = new Player(Player::parseUnitPlayer("units/7.json"));
        ASSERT_EQ(p1->getName(),p1ok->getName());
        ASSERT_EQ(p1->getDamage(),p1ok->getDamage());
        ASSERT_EQ(p1->getHp(),p1ok->getHp());
        ASSERT_EQ(p1->getCooldown(), p1ok->getCooldown());
        ASSERT_EQ(p2->getName(),p2ok->getName());
        ASSERT_EQ(p2->getDamage(),p2ok->getDamage());
        ASSERT_EQ(p2->getHp(),p2ok->getHp());
        ASSERT_EQ(p1->getCooldown(), p1ok->getCooldown());
        ASSERT_EQ(p2->getCooldown(), p2ok->getCooldown());
        p1->Attack(p2);
        EXPECT_EQ(p1->getStringvar(),expected);
        delete p1;
        delete p2;
    });
}
int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}