#pragma once
#include "direction.hpp"
#include "entity.hpp"

class Bullet : public Entity
{
    public:
        Bullet();
        void setDirection(Direction direction);
        virtual void update() override;
        bool isDead() const;
        int32_t damage() const;
        virtual bool handleCollision() override;
    protected:
        Direction mDirection;
        uint32_t mTtl;
        int32_t mDamage;
        bool mDead;
};

class PistolBullet : public Bullet
{
    public:
        PistolBullet(Direction direction);
};

class MiniBullet : public Bullet
{
    public:
        MiniBullet(Direction direction);
};
