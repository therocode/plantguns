#include "entity.hpp"
#include <iostream>

Entity::Entity():
    mQuad({32.0f, 32.0f}),
    mColoriser(fea::Color::White),
    mCollisionTiles(nullptr)
{
}
        
void Entity::renderMe(fea::Renderer2D& renderer)
{
    renderer.queue(mQuad);
}

void Entity::setPosition(const glm::vec2& position)
{
    mQuad.setPosition(position);
    mPosition = position;
}

const glm::vec2& Entity::position() const
{
    return mPosition;
}

void Entity::translate(const glm::vec2& amount)
{
    setPosition(mPosition + amount);
}

void Entity::setSize(const glm::vec2& size)
{
    mQuad.setSize(size);
}
        
glm::vec2 Entity::size() const
{
    return mQuad.getSize();
}

glm::vec2 Entity::center() const
{
    return position() + size() / 2.0f;
}

void Entity::setTexture(const fea::Texture& texture)
{
    mQuad.setTexture(texture);
}

void Entity::update()
{
    mVelocity += mAcceleration;
    glm::vec2 totalVel = mVelocity + mKnockVel;

    glm::vec2 oldPos = mPosition;

    translate({totalVel.x, 0.0f});
    if(collides())
        setPosition({oldPos.x, mPosition.y});

    translate({0.0f, totalVel.y});
    if(collides())
        setPosition({mPosition.x, oldPos.y});

    mKnockVel /= 1.5f;

    if(glm::length(mKnockVel) < 1.0f)
        mKnockVel = {0.0f, 0.0f};

    if(mColoriser != fea::Color::White)
    {
        mColoriser += fea::Color(0.05f, 0.05f, 0.05f);

        mQuad.setColor(mColoriser);
    }
}

void Entity::knock(const glm::vec2& knockVector, float power)
{
    if(glm::length(knockVector))
        mKnockVel = glm::normalize(knockVector) * power;
}

void Entity::knockFrom(const glm::vec2& knockPosition, float power)
{
    mKnockVel = glm::normalize((center() - knockPosition)) * power;
}

void Entity::colorize(const fea::Color& color)
{
    mColoriser = color;
}

bool Entity::isDead() const
{
    return mHealth <= 0;
}

int32_t Entity::health() const
{
    return mHealth;
}

void Entity::setCollisionMap(const TileMap& tiles)
{
    mCollisionTiles = &tiles;
}

const glm::vec2& Entity::collisionStart() const
{
    return mCollisionStart;
}

const glm::vec2& Entity::collisionSize() const
{
    return mCollisionSize;
}

bool Entity::collides() const
{
    if(mCollisionTiles)
    {
        glm::vec2 collStart = position() + mCollisionStart;
        glm::vec2 collEnd = collStart + mCollisionSize;


        return pointCollides(collStart) ||
               pointCollides({collStart.x, collEnd.y}) ||
               pointCollides({collEnd.x, collStart.y}) ||
               pointCollides(collEnd);
    }

    else return false;
}

bool Entity::pointCollides(const glm::vec2& point) const
{
    glm::uvec2 tile = (glm::uvec2) (glm::floor(point / 32.0f));

    if(tile.x > 39 || tile.y > 23)
        return true;

    TileType type = getTile(*mCollisionTiles, tile);
    if(type != GRASS && type != PLOT)
        return true;

    return false;
}
