#pragma once
#include "direction.hpp"
#include "entity.hpp"
#include "directionresolver.hpp"
#include "weapons.hpp"

enum PlantId {PISTOL};

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
        bool isDead() const;
    private:
        float mRunSpeed;
        DirectionResolver mDirectionResolver;
        Direction mFireDirection;
        std::unique_ptr<Weapon> mWeapon;

        uint32_t mInvisibilityTimer;
        int32_t mHealth;
};
