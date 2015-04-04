#include "entity.hpp"
#include <iostream>

Entity::Entity():
    mQuad({32.0f, 32.0f}),
    mColoriser(fea::Color::White)
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
    translate(mVelocity + mKnockVel);

    mKnockVel /= 1.5f;

    if(glm::length(mKnockVel) < 1.0f)
        mKnockVel = {0.0f, 0.0f};

    if(mColoriser != fea::Color::White)
    {
        mColoriser += fea::Color(0.05f, 0.05f, 0.05f);

        mQuad.setColor(mColoriser);
    }
}

void Entity::knock(const glm::vec2& knockVector)
{
    mKnockVel = knockVector;
}

void Entity::knockFrom(const glm::vec2& knockPosition, float power)
{
    mKnockVel = glm::normalize((center() - knockPosition)) * power;
}

void Entity::colorize(const fea::Color& color)
{
    mColoriser = color;
}
