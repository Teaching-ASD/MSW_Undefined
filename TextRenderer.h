#pragma once
#include "Renderer.h"
#include <ostream>

class TextRenderer: public Renderer{
    protected: 
    std::ostream& out;
    public:
    TextRenderer(std::ostream &os = std::cout): out(os){};
    void setOutputStream(const std::ostream &os);
};