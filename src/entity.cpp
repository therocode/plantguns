#include "entity.hpp"

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
}

void Entity::setSize(const glm::vec2& size)
{
    mQuad.setSize(size);
}

void Entity::setTexture(const fea::Texture& texture)
{
    mQuad.setTexture(texture);
}
