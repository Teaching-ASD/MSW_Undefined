/**
 * \class TextRenderer
 *
 * \brief TextRenderer class
 *
 * This is a TextRenderer class which renders the
 *
 * \author LeviG9901, 97Vix, b3nc301
 * 
 * \version 1.0
 *
 * \date 2020.12.06. 22:12
 *
 * Created on: 2020.12.06. 22:12
*/
#pragma once
#include "Renderer.h"
#include <ostream>

class TextRenderer: public Renderer{
    protected: 
    std::ostream& out;///This is the output file reference
    public:
    ///This is constructor for the TextRenderer
    TextRenderer(std::ostream &os = std::cout/**< [in]  This is an outputfile reference*/): out(os){};
    ///This method is for setting the Output Stream
    void setOutputStream(const std::ostream &os/**< [in]  This is an outputfile reference*/);
};