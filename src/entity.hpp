#pragma once
#include <fea/render2d.hpp>

class Entity
{
    public:
        Entity();
        void renderMe(fea::Renderer2D& renderer);
        void setPosition(const glm::vec2& position);
        const glm::vec2& position() const;
        void translate(const glm::vec2& amount);
        void setSize(const glm::vec2& size);
        glm::vec2 size() const;
        void setTexture(const fea::Texture& texture);
        virtual void update();
    protected:
        glm::vec2 mPosition;
        fea::Quad mQuad;
        glm::vec2 mVelocity;
        glm::vec2 mAcceleration;
};
