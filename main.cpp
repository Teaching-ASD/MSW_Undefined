#include <iostream>
#include <fstream>
#include "Hero.h"


using namespace std;

int main(int argc, char *argv[])
{
    if(argc==3)
    {
        try
        {
            Hero* h1 = new Hero(Hero::parseUnit(argv[1]));
            Hero* h2 = new Hero(Hero::parseUnit(argv[2]));
            h1->Attack(h2);
            cout <<h1->getStringvar()<<endl;
            delete h1, h2;
        }
        catch(std::exception const& e)
        {
            cerr<<e.what()<<endl;
	    return 1;
        }
    }
    else{
        cerr<<"Please give exactly 2 file!" << endl;
    }

    return 0;
}
