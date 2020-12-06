#pragma once
#include"SVGRenderer.h"
#include<iostream>
#include <filesystem>

class ObserverSVGRenderer : public SVGRenderer{
    public:
        void render(const Game& gm) const override;
        explicit ObserverSVGRenderer(const std::string &os) : SVGRenderer(os){}
};