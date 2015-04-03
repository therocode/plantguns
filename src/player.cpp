#include "player.hpp"
       
Player::Player()
{
    setSize({32.0f, 32.0f});
}

void Player::addMove(Direction d)
{
    if(d == UP)
        mDirectionResolver.upActive(true);
    else if(d == DOWN)
        mDirectionResolver.downActive(true);
    else if(d == LEFT)
        mDirectionResolver.leftActive(true);
    else if(d == RIGHT)
        mDirectionResolver.rightActive(true);
}

void Player::delMove(Direction d)
{
    if(d == UP)
        mDirectionResolver.upActive(false);
    else if(d == DOWN)
        mDirectionResolver.downActive(false);
    else if(d == LEFT)
        mDirectionResolver.leftActive(false);
    else if(d == RIGHT)
        mDirectionResolver.rightActive(false);
}

void Player::update()
{
    glm::vec2 playerDir = mDirectionResolver.getDirection();

    glm::vec2 targetVel = playerDir * 2.5f;
    glm::vec2 currentVel = mVelocity;

    glm::vec2 acc = (targetVel - currentVel) / 1.0f;  //  / timestep
    float maxAcc = 0.5f;

    if(acc.x > maxAcc)
        acc.x = maxAcc;
    if(acc.y > maxAcc)
        acc.y = maxAcc;

    mAcceleration = acc;

    Entity::update();
}
