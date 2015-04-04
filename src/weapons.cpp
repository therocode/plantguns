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

const std::string Weapon::name() const
{
    return mName;
}

uint32_t Weapon::ammo() const
{
    return mAmmo;
}

bool Weapon::isOut() const
{
    return mAmmo == 0;
}

void Weapon::resetTimer()
{
    mBulletTimer = 300 - mFireRate;
}

Pistol::Pistol(const std::unordered_map<std::string, fea::Texture>& textures):
    Weapon::Weapon(textures, 260)
{
    mAmmo = 14;
    mName = "Pistol";
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
        --mAmmo;
        
        return result;
    }
    else
    {
        return result;
    }
}

Shotgun::Shotgun(const std::unordered_map<std::string, fea::Texture>& textures):
    Weapon::Weapon(textures, 230)
{
    mAmmo = 8;
    mName = "Shotgun";
}

std::vector<std::unique_ptr<Bullet>> Shotgun::getBullets(const glm::vec2& position)
{
    std::vector<std::unique_ptr<Bullet>> result;

    if(mBulletReady)
    {
        for(int32_t i = 0; i < 20; i++)
        {
            auto bullet = std::unique_ptr<Bullet>(new MiniBullet(mDirection));
            bullet->setPosition(position - glm::vec2(4.0f, 4.0f));
            bullet->setTexture(mTextures.at("minibullet"));

            result.push_back(std::move(bullet));
        }

        --mAmmo;
        
        mBulletReady = false;
        return result;
    }
    else
    {
        return result;
    }
}
