#include <iostream>
#include "Hero.h"

using namespace std;

int main()
{
    Hero Levi = Hero("Levi",10,100);
    Hero Kalman = Hero("Kalman",20,200);

    cout << "Name: " << Levi.getName() << ", Damage: " << Levi.getDamage() << ", HP: " << Levi.getHp() << endl;
    cout << "Name: " << Kalman.getName() << ", Damage: " << Kalman.getDamage() << ", HP: " << Kalman.getHp() << endl;
}
