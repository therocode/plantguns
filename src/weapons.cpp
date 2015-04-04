#include "weapons.hpp"
#include <iostream>

Weapon::Weapon(const std::unordered_map<std::string, fea::Texture>& textures, uint32_t fireRate):
    mTextures(textures),
    mDirection(NONE),
    mIsFiring(false),
    mFireRate(fireRate)
{
    resetTimer();
}

void Weapon::startFire(Direction direction)
{
    resetTimer();
    mDirection = direction;
    mIsFiring = true;
}

void Weapon::stopFire()
{
    mDirection = NONE;
    mIsFiring = false;
    resetTimer();
}

void Weapon::update()
{
    if(mIsFiring)
    {
        if(mBulletTimer > 0)
            --mBulletTimer;
        else
        {
            mBulletReady = true;
            resetTimer();
        }
    }
}

void Weapon::resetTimer()
{
    mBulletTimer = 300 - mFireRate;
}

Pistol::Pistol(const std::unordered_map<std::string, fea::Texture>& textures):
    Weapon::Weapon(textures, 295)
{
}

std::vector<std::unique_ptr<Bullet>> Pistol::getBullets(const glm::vec2& position)
{
    std::vector<std::unique_ptr<Bullet>> result;

    if(mBulletReady)
    {
        auto bullet = std::unique_ptr<Bullet>(new PistolBullet(mDirection));
        bullet->setPosition(position - glm::vec2(4.0f, 4.0f));
        bullet->setTexture(mTextures.at("bullet"));

        result.push_back(std::move(bullet));

        mBulletReady = false;
        
        return result;
    }
    else
    {
        return result;
    }
}
