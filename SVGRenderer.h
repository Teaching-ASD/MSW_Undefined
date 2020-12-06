#pragma once
#include "Renderer.h"
#include <ostream>

class SVGRenderer: public Renderer{
    protected: 
    std::string fname;
    public:
    explicit SVGRenderer(const std::string &fname_): fname(fname_){};
};