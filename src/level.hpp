#pragma once
#include <fea/render2d.hpp>

class Level
{
    public:
        Level();
        void renderMe(fea::Renderer2D& renderer);
        void setTexture(fea::Texture& texture);
    private:
        fea::TileMap mTiles;
};
