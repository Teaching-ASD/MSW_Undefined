/**
 * \class HeroTextRenderer
 *
 * \brief HeroTextRenderer class
 *
 * This is a HeroTextRenderer class which renders the map out, but only until the distance of the light radius to an ostream
 *
 * \author LeviG9901, 97Vix, b3nc301
 * 
 * \version 1.0
 *
 * \date 2020.12.06. 21:50
 *
 * Created on: 2020.12.06. 21:50
*/
#pragma once
#include"TextRenderer.h"
#include<iostream>

class HeroTextRenderer : public TextRenderer{
    public:
        ///This method is for print out the datas to the file
        void render(const Game& gm/**< [in]  This is a game object reference*/) const override;
        ///This is a contructor and it needs a filename equals std::cout
        HeroTextRenderer(std::ostream& os = std::cout) : TextRenderer(os){}
};