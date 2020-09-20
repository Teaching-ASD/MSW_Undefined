#include <iostream>
#include "Arena.h"
#include "Hero.h"


using namespace std;

int main(int argc, char *argv[])
{
    if(argc==7)
    {
    Arena* Fight = new Arena();
    try{
    Fight->addHero(Hero(argv[1],stoi(argv[2]),stoi(argv[3])));
    Fight->addHero(Hero(argv[4],stoi(argv[5]),stoi(argv[6])));
    cout<<Fight->Fight()<<endl;
    }
    catch(const std::invalid_argument& ia)
    {
        	  std::cerr << "Invalid argument: " << ia.what() << ". Please give the correct arguments. \n";
    }
    delete Fight;
    return 0;
    }
    else{
        cout << "Not valid arguments, please give 6 arguments." << endl;
        return 100;
    }
}
