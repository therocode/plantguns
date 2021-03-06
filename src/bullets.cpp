#include "bullets.hpp"
#include <glm/gtx/rotate_vector.hpp>
#include <random>

Bullet::Bullet():
    mDead(false)
{
}

void Bullet::setDirection(Direction direction)
{
    mDirection = direction;
}
        
void Bullet::update()
{
    Entity::update();
    if(mTtl > 0)
        mTtl--;
    else
        mDead = true;
}

bool Bullet::isDead() const
{
    return mDead;
}

int32_t Bullet::damage() const
{
    return mDamage;
}

bool Bullet::handleCollision()
{
    mDead = true;
    return false;
}

PistolBullet::PistolBullet(Direction direction)
{
    mTtl = 60;
    mDamage = 6;
    mCollisionSize = glm::vec2(8.0f, 8.0f);

    if(direction == NONE)
        direction = RIGHT;

    setDirection(direction);

    mQuad.setSize({8.0f, 8.0f});
    mVelocity = toVector(mDirection) * 5.0f;
}

MiniBullet::MiniBullet(Direction direction)
{
    std::random_device rd;
    std::uniform_int_distribution<> randTtl(15, 50);
    std::uniform_int_distribution<> angleChange(-10, 10);
    std::uniform_int_distribution<> velocity(0, 40);
    mTtl = randTtl(rd);
    mDamage = 3;
    mCollisionSize = glm::vec2(4.0f, 4.0f);

    if(direction == NONE)
        direction = RIGHT;

    setDirection(direction);

    mQuad.setSize({4.0f, 4.0f});
    auto directionVec = glm::rotate(toVector(mDirection), glm::radians((float)angleChange(rd)));
    mVelocity = directionVec * (3.0f + (velocity(rd))/10.0f);
}
