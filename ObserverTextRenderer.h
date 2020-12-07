/**
 * \class ObserverTextRenderer
 *
 * \brief ObserverTextRenderer class
 *
 * This is a ObserverTextRenderer which renders the full map out to an ostream
 *
 * \author LeviG9901, 97Vix, b3nc301
 * 
 * \version 1.0
 *
 * \date 2020.12.06. 22:05
 *
 * Created on: 2020.12.06. 22:05
*/
#pragma once
#include"TextRenderer.h"
#include<iostream>

class ObserverTextRenderer : public TextRenderer{
    public:
        ///This method is for print out the datas to the file
        void render(const Game&) const override;
        ///This is a constructor which needs a filename reference
        ObserverTextRenderer(std::ostream& os = std::cout) : TextRenderer(os){}

};