#pragma once
#include "direction.hpp"
#include "entity.hpp"
#include "directionresolver.hpp"
#include "weapons.hpp"

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
        int32_t plantId() const;
        void giveWeapon(std::unique_ptr<Weapon> weapon);
        Weapon* weapon();
        void hit(Enemy& enemy);
        void toggleWeapon();
        void toggleSeed();
    private:
        Weapon* currentWeapon() const;
        float mBaseRunSpeed;
        float mRunSpeed;
        DirectionResolver mDirectionResolver;
        Direction mFireDirection;
        std::vector<std::unique_ptr<Weapon>> mWeapons;
        uint32_t mCurrentWeaponIndex;

        uint32_t mInvisibilityTimer;
};
