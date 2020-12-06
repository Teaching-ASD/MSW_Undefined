#pragma once
#include"TextRenderer.h"
#include<iostream>

class HeroTextRenderer : public TextRenderer{
    public:
        void render(const Game& gm) const override;
        HeroTextRenderer(std::ostream& os = std::cout) : TextRenderer(os){}
};