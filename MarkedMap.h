/**
 * \class MarkedMap
 *
 * \brief MarkedMap class
 *
 * This is a MarkedMap class which reads in the MarkedMap file
 *
 * \author LeviG9901, 97Vix, b3nc301
 * 
 * \version 1.0
 *
 * \date 2020.12.06. 21:55
 *
 * Created on: 2020.12.06. 21:55
*/
#pragma once
#include<string>
#include "Map.h"

class MarkedMap: public Map{
public:
    ///This is a constructor for MarkedMap
    explicit MarkedMap(std::string filename/**< [in] The filename string */);
    ///This is an empty constructor for Map
    MarkedMap(){};
    ///This method is for giving back a HeroPosition coordinates in pair
    std::pair<int,int> getHeroPosition() const;
    ///This method is for giving back the Monsters position coordinates in pair type vector
    std::vector<std::pair<int,int>> getMonsterPositions(char /**< [in] This is a monstertype char */) const;

};