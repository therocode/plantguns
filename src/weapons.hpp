#pragma once
#include <unordered_map>
#include <fea/render2d.hpp>
#include "bullets.hpp"
#include "direction.hpp"

class Player;

class Weapon
{
    public:
        Weapon(const std::unordered_map<std::string, fea::Texture>& textures, uint32_t fireRate);
        void startFire(Direction direction);
        void stopFire();
        void update();
        virtual std::vector<std::unique_ptr<Bullet>> getBullets(const glm::vec2& position, Player& player) = 0;
        const std::string name() const;
        uint32_t ammo() const;
        bool isOut() const;
    protected:
        void resetTimer(bool reduced = false);
        Direction mDirection;
        bool mIsFiring;
        uint32_t mFireRate;
        bool mBulletReady;
        uint32_t mBulletTimer;
        const std::unordered_map<std::string, fea::Texture>& mTextures;
        std::string mName;
        uint32_t mAmmo;
};

class Pistol : public Weapon
{
    public:
        Pistol(const std::unordered_map<std::string, fea::Texture>& textures);
        virtual std::vector<std::unique_ptr<Bullet>> getBullets(const glm::vec2& position, Player& player);
};

class Shotgun : public Weapon
{
    public:
        Shotgun(const std::unordered_map<std::string, fea::Texture>& textures);
        virtual std::vector<std::unique_ptr<Bullet>> getBullets(const glm::vec2& position, Player& player);
};
