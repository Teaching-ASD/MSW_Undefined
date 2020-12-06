#pragma once
#include"TextRenderer.h"
#include<iostream>

class ObserverTextRenderer : public TextRenderer{
    public:
        void render(const Game&) const override;
        ObserverTextRenderer(std::ostream& os = std::cout) : TextRenderer(os){}

};