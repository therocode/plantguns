#include "enemies.hpp"
#include "bullets.hpp"
#include <iostream>
    
bool Enemy::isDead() const
{
    return mHealth <= 0;
}

void Enemy::hit(Bullet& bullet)
{
    mHealth -= bullet.damage();
}

Spikey::Spikey()
{
    mQuad.setSize({16.0f, 16.0f});
    mHealth = 15;
}
