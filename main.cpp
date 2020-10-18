#include <iostream>
#include <fstream>
#include "Hero.h"
#include "Json.h"
#include "Player.h"


using namespace std;

int main(int argc, char *argv[])
{

    
    if(argc==3)
    {
        try
        {
            Player* h1 = new Player(Player::parseUnitPlayer(argv[1]));
            Player* h2 = new Player(Player::parseUnitPlayer(argv[2]));

            h1->Attack(h2);
            cout <<h1->getStringvar()<<endl;
            delete h1;
            delete h2;
        }
        catch(std::exception const& e)
        {
            cerr<< "Error, " <<e.what()<<endl;
	    return 1;
        }
    }
    else{
        cerr<<"Please give exactly 2 file!" << endl;
    }
    return 0;
}
