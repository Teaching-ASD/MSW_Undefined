#include <iostream>
#include "Arena.h"

using namespace std;

int main()
{
    Hero Levi = Hero("Levi",10,100);
    Hero Kalman = Hero("Kalman",20,200);

    Arena Fight = Arena(&Levi,&Kalman);

    cout<<Fight.Attack()<<endl;

    return 0;
}
