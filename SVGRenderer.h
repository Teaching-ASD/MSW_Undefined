/**
 * \class SVGRenderer
 *
 * \brief SVGRenderer class
 *
 * This is a SVGRenderer abstract class
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

class SVGRenderer: public Renderer{
    protected: 
    std::string fname;///This is a filename string
    public:
    ///This is a constructor for SVGRenderer
    explicit SVGRenderer(const std::string &fname_/**< [in]  This is a filename reference*/): fname(fname_){};
};