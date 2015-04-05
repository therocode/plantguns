#pragma once
#include "direction.hpp"
#include "entity.hpp"
#include "directionresolver.hpp"
#include "weapons.hpp"
#include "seedbag.hpp"

class Enemy;

class Player : public Entity
{
    public:
        Player();
        void addMove(Direction d);
        void delMove(Direction d);
        void addFire(Direction d);
        void delFire(Direction d);
        virtual void update() override;
        void giveWeapon(std::unique_ptr<Weapon> weapon);
        void giveSeeds(SeedBag bag);
        Weapon* weapon();
        SeedBag* seedBag();
        void usedSeed();
        void hit(Enemy& enemy);
        void toggleWeapon();
        void toggleSeed();
        void heal(int32_t amount);
    private:
        Weapon* currentWeapon();
        SeedBag* currentSeedBag();
        float mBaseRunSpeed;
        float mRunSpeed;
        DirectionResolver mDirectionResolver;
        Direction mFireDirection;
        std::vector<std::unique_ptr<Weapon>> mWeapons;
        uint32_t mCurrentWeaponIndex;
        std::vector<SeedBag> mSeeds;
        uint32_t mCurrentSeedIndex;

        uint32_t mInvisibilityTimer;
};
