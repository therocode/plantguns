#pragma once
#include "entity.hpp"

class Bullet;

enum EnemyType {SPIKEY};

class Enemy : public Entity
{
    public:
        bool isDead() const;
        void hit(Bullet& bullet);
        int32_t damage() const;
    protected:
        int32_t mHealth;
        int32_t mDamage;
};

class Spikey : public Enemy
{
    public:
        Spikey();
};
