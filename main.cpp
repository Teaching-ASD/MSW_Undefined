
#include <iostream>
#include <fstream>
#include "Arena.h"
#include "Hero.h"
#include "Player.h"


using namespace std;

int main(int argc, char *argv[])
{

    
    if(argc==3)
    {
        Arena* Fight = new Arena();
        try
        {
        Fight->addHero(Player::parseUnit(argv[1]));
        Fight->addHero(Player::parseUnit(argv[2]));
        }
        catch(std::exception const& e)
        {
            cerr<<e.what()<<endl;
	    return 1;
        }
        cout<<Fight->Fight()<<endl;
        delete Fight;
        }
    else{
        cerr<<"Please give exactly 2 file!" << endl;
    }
    

    return 0;
}
