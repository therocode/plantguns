#pragma once
#include <fea/render2d.hpp>
#include "tilemap.hpp"

const fea::Color redHurtColor(0.8f, 0.2f, 0.3f);
const fea::Color orangeHurtColor(0.8f, 0.5f, 0.3f);

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
        glm::vec2 center() const;
        void setTexture(const fea::Texture& texture);
        virtual void update();
        void knock(const glm::vec2& knockVector, float power);
        void knockFrom(const glm::vec2& knockPosition, float power);
        void colorize(const fea::Color& color);
        bool isDead() const;
        int32_t health() const;
        void setCollisionMap(const TileMap& tiles);
        const glm::vec2& collisionStart() const;
        const glm::vec2& collisionSize() const;
        virtual bool handleCollision();
    protected:
        bool collides() const;
        bool pointCollides(const glm::vec2& point) const;
        glm::vec2 mCollisionStart;
        glm::vec2 mCollisionSize;
        glm::vec2 mPosition;
        fea::Quad mQuad;
        glm::vec2 mVelocity;
        glm::vec2 mAcceleration;
        glm::vec2 mKnockVel;
        fea::Color mColoriser;
        int32_t mHealth;
        const TileMap* mCollisionTiles;
};
