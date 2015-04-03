#pragma once
#include <fea/render2d.hpp>

class Entity
{
    public:
        Entity();
        void renderMe(fea::Renderer2D& renderer);
        void setPosition(const glm::vec2& position);
        void setSize(const glm::vec2& size);
        void setTexture(const fea::Texture& texture);
    private:
        glm::vec2 mPosition;
        fea::Quad mQuad;
};
