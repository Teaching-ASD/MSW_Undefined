#pragma once
#include"SVGRenderer.h"
#include<iostream>
#include <filesystem>

class CharacterSVGRenderer : public SVGRenderer{
    public:
        void render(const Game& gm) const override;
        explicit CharacterSVGRenderer(const std::string &os) : SVGRenderer(os){}
};