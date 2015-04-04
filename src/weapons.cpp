#include "weapons.hpp"
#include <iostream>
#include "player.hpp"

Weapon::Weapon(const std::unordered_map<std::string, fea::Texture>& textures, uint32_t fireRate):
    mTextures(textures),
    mDirection(NONE),
    mIsFiring(false),
    mFireRate(fireRate),
    mSpeedMultiplier(1.0f)
{
    resetTimer();
}

void Weapon::startFire(Direction direction)
{
    resetTimer(true);
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

void Weapon::addAmmo(uint32_t ammo)
{
    mAmmo += ammo;
}

bool Weapon::isOut() const
{
    return mAmmo == 0;
}

float Weapon::speedMultiplier() const
{
    return mSpeedMultiplier;
}

void Weapon::resetTimer(bool reduced)
{
    mBulletTimer = (300 - mFireRate) / (reduced ? 5 : 1);
}

Pistol::Pistol(const std::unordered_map<std::string, fea::Texture>& textures):
    Weapon::Weapon(textures, 260)
{
    mAmmo = 14;
    mName = "Pistol";
    mSpeedMultiplier = 0.7f;
}

std::vector<std::unique_ptr<Bullet>> Pistol::getBullets(const glm::vec2& position, Player& player)
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

WeaponType Pistol::type()
{
    return PISTOL;
}

Shotgun::Shotgun(const std::unordered_map<std::string, fea::Texture>& textures):
    Weapon::Weapon(textures, 230)
{
    mAmmo = 8;
    mName = "Shotgun";
    mSpeedMultiplier = 0.5f;
}

std::vector<std::unique_ptr<Bullet>> Shotgun::getBullets(const glm::vec2& position, Player& player)
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

        player.knock(-toVector(mDirection), 5.0f);
        --mAmmo;
        
        mBulletReady = false;
        return result;
    }
    else
    {
        return result;
    }
}

WeaponType Shotgun::type()
{
    return SHOTGUN;
}
