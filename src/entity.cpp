#include "entity.hpp"
#include <iostream>

Entity::Entity():
    mQuad({32.0f, 32.0f})
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

void Entity::translate(const glm::vec2& amount)
{
    setPosition(mPosition + amount);
}

void Entity::setSize(const glm::vec2& size)
{
    mQuad.setSize(size);
}

void Entity::setTexture(const fea::Texture& texture)
{
    mQuad.setTexture(texture);
}

void Entity::update()
{
    mVelocity += mAcceleration;
    translate(mVelocity);
}
