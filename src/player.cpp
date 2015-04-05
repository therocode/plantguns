#include "player.hpp"
#include "enemies.hpp"
#include "accelerator.hpp"
#include <iostream>
       
Player::Player():
    mBaseRunSpeed(3.0f),
    mRunSpeed(3.0f),
    mFireDirection(NONE),
    mInvisibilityTimer(0),
    mCurrentWeaponIndex(0),
    mCurrentSeedIndex(0)
{
    mHealth = 100;
    mCollisionStart = glm::vec2(8.0f, 8.0f);
    mCollisionSize = glm::vec2(16.0f, 16.0f);
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
    if(currentWeapon())
    {
        mRunSpeed = mBaseRunSpeed * currentWeapon()->speedMultiplier();
        currentWeapon()->startFire(d);
    }
}

void Player::delFire(Direction d)
{
    if(d == mFireDirection)
    {
        mFireDirection = NONE;
        if(currentWeapon())
            currentWeapon()->stopFire();
        mRunSpeed = mBaseRunSpeed;
    }
}

void Player::update()
{
    glm::vec2 playerDir = mDirectionResolver.getDirection();

    Accelerator accelerator;
    mAcceleration = accelerator.get(playerDir, mRunSpeed, mVelocity, 0.5f);


    if(currentWeapon())
    {
        if(currentWeapon()->isOut())
        {
            mWeapons.erase(mWeapons.begin() + mCurrentWeaponIndex);
            mCurrentWeaponIndex = 0;
        }
        
        if(currentWeapon())
            currentWeapon()->update();
    }

    if(mInvisibilityTimer > 0)
        --mInvisibilityTimer;

    Entity::update();
}

void Player::giveWeapon(std::unique_ptr<Weapon> weapon)
{
    bool merged = false;
    for(auto& currentWeapon : mWeapons)
    {
        if(currentWeapon->type() == weapon->type())
        {
            currentWeapon->addAmmo(weapon->ammo());
            merged = true;
            break;
        }
    }

    if(!merged)
        mWeapons.push_back(std::move(weapon));
}

void Player::giveSeeds(SeedBag bag)
{
    bool merged = false;
    for(auto& currentSeed : mSeeds)
    {
        if(currentSeed.type == bag.type)
        {
            currentSeed.amount += bag.amount;
            merged = true;
            break;
        }
    }

    if(!merged)
        mSeeds.push_back(bag);
}

Weapon* Player::weapon()
{
    if(currentWeapon())
        return currentWeapon();
    else
        return nullptr;
}

SeedBag* Player::seedBag()
{
    if(currentSeedBag())
        return currentSeedBag();
    else
        return nullptr;
}

void Player::usedSeed()
{
    SeedBag* bag = currentSeedBag();

    bag->amount--;

    if(bag->amount == 0)
    {
        mSeeds.erase(mSeeds.begin() + mCurrentSeedIndex);
        mCurrentSeedIndex = 0;
    }
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

void Player::toggleWeapon()
{
    mCurrentWeaponIndex++;

    if(mCurrentWeaponIndex >= mWeapons.size())
        mCurrentWeaponIndex = 0;
}

void Player::toggleSeed()
{
    mCurrentSeedIndex++;

    if(mCurrentSeedIndex >= mSeeds.size())
        mCurrentSeedIndex = 0;
}

void Player::heal(int32_t amount)
{
    mHealth = std::min(100, mHealth + amount);
}

Weapon* Player::currentWeapon()
{
    if(mCurrentWeaponIndex < mWeapons.size())
        return &*mWeapons[mCurrentWeaponIndex];
    else
        return nullptr;
}

SeedBag* Player::currentSeedBag()
{
    if(mCurrentSeedIndex < mSeeds.size())
        return &mSeeds[mCurrentSeedIndex];
    else
        return nullptr;
}
