/**
 * \class ObserverSVGRenderer
 *
 * \brief ObserverSVGRenderer class
 *
 * This is a ObserverSVGRenderer class which renders the full map out to an svg file
 *
 * \author LeviG9901, 97Vix, b3nc301
 * 
 * \version 1.0
 *
 * \date 2020.12.06. 22:00
 *
 * Created on: 2020.12.06. 22:00
*/
#pragma once
#include"SVGRenderer.h"
#include<iostream>
#include <filesystem>

class ObserverSVGRenderer : public SVGRenderer{
    public:
        ///This method is for print out the datas to the file
        void render(const Game& gm/**< [in]  This is a game object reference*/) const override;
        ///This is a constructor which needs a filename reference
        explicit ObserverSVGRenderer(const std::string &os) : SVGRenderer(os){}
};