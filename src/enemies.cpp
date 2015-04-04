#include "enemies.hpp"
    
bool Enemy::isDead() const
{
    return false;
}

Spikey::Spikey()
{
    mQuad.setSize({16.0f, 16.0f});
}
