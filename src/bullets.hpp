#pragma once
#include "direction.hpp"
#include "entity.hpp"

class Bullet : public Entity
{
    public:
        void setDirection(Direction direction);
        virtual void update() override;
        bool isDead() const;
        int32_t damage() const;
    protected:
        Direction mDirection;
        uint32_t mTtl;
        int32_t mDamage;
};

class PistolBullet : public Bullet
{
    public:
        PistolBullet(Direction direction);
};
