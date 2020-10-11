#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Hero.h"
#include <math.h>

class Player : public Hero
{
private:

int maxHP;
int CurHP;
int CurDMG;
int XP=0;

public:
Player(std::string,int,const int);
~Player(){};


static Player parseUnit(std::string fname);

int getCurDMG();
int getCurHP();

void addXP();
void levelUp();
void ChangeCurHp(int); 

};
#endif //Player_H