/**
 * \class CharacterSVGRenderer
 *
 * \brief CharacterSVGRenderer class
 *
 * This is a CharacterSVGRenderer class which renders the map out, but only until the distance of the light radius to an svg file
 *
 * \author LeviG9901, 97Vix, b3nc301
 * 
 * \version 1.0
 *
 * \date 2020.12.06. 21:30
 *
 * Created on: 2020.12.06. 21:30
*/
#pragma once
#include"SVGRenderer.h"
#include<iostream>
#include <filesystem>

class CharacterSVGRenderer : public SVGRenderer{
    public:
        ///This method is for print out the datas to the file
        void render(const Game& gm/**< [in]  This is a game object reference*/) const override;
        ///This is a constructor which needs a filename reference
        explicit CharacterSVGRenderer(const std::string &os) : SVGRenderer(os){}
};