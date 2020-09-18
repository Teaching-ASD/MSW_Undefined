#include <iostream>
#include "Arena.h"

using namespace std;

int main()
{
    Hero Levi = Hero("Levi",10,100);
    Hero Kalman = Hero("Kalman",20,200);

    Arena Fight = Arena(&Levi,&Kalman);


    cout << "Name: " << Levi.getName() << ", Damage: " << Levi.getDamage() << ", HP: " << Levi.getHp() << endl;
    cout << "Name: " << Kalman.getName() << ", Damage: " << Kalman.getDamage() << ", HP: " << Kalman.getHp() << endl;

    return 0;
}
