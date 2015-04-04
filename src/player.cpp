#include "player.hpp"
#include "enemies.hpp"
#include "accelerator.hpp"
#include <iostream>
       
Player::Player():
    mRunSpeed(3.0f),
    mFireDirection(NONE),
    mInvisibilityTimer(0)
{
    mHealth = 100;
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

void Player::addFire(Direction d)
{
    mFireDirection = d;
    if(mWeapon)
    {
        mRunSpeed = 1.5f;
        mWeapon->startFire(d);
    }
}

void Player::delFire(Direction d)
{
    if(d == mFireDirection)
    {
        mFireDirection = NONE;
        if(mWeapon)
            mWeapon->stopFire();
        mRunSpeed = 3.0f;
    }
}

void Player::update()
{
    glm::vec2 playerDir = mDirectionResolver.getDirection();

    Accelerator accelerator;
    mAcceleration = accelerator.get(playerDir, mRunSpeed, mVelocity, 0.5f);


    if(mWeapon)
    {
        if(mWeapon->isOut())
            mWeapon = nullptr;
        
        if(mWeapon)
            mWeapon->update();
    }

    if(mInvisibilityTimer > 0)
        --mInvisibilityTimer;

    Entity::update();
}

int32_t Player::plantId() const
{
    return PISTOL;
}
        
void Player::giveWeapon(std::unique_ptr<Weapon> weapon)
{
    mWeapon = std::move(weapon);
}

Weapon* Player::weapon()
{
    if(mWeapon)
        return &*mWeapon;
    else
        return nullptr;
}

void Player::hit(Enemy& enemy)
{
    knockFrom(enemy.center(), 6.0f);
    enemy.knockFrom(center(), 4.0f);

    if(mInvisibilityTimer == 0)
    {
        colorize(redHurtColor);
        mHealth -= enemy.damage();
        mInvisibilityTimer = 30;
    }
}
