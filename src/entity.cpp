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

void Entity::setTexture(const fea::Texture& texture)
{
    mQuad.setTexture(texture);
}

void Entity::update()
{
    mVelocity += mAcceleration;
    translate(mVelocity);
}
