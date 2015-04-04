#include "bullets.hpp"

void Bullet::setDirection(Direction direction)
{
    mDirection = direction;
}
        
void Bullet::update()
{
    Entity::update();
    if(mTtl > 0)
        mTtl--;
}

bool Bullet::isDead() const
{
    return mTtl == 0;
}

PistolBullet::PistolBullet(Direction direction)
{
    mTtl = 60;

    if(direction == NONE)
        direction = RIGHT;

    setDirection(direction);

    mQuad.setSize({8.0f, 8.0f});
    mVelocity = toVector(mDirection) * 5.0f;
}
