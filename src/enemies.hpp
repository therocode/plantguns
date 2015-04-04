#pragma once
#include "entity.hpp"

class Bullet;

enum EnemyType {SPIKEY};

class Enemy : public Entity
{
    public:
        bool isDead() const;
        void hit(Bullet& bullet);
    protected:
        int32_t mHealth;
};

class Spikey : public Enemy
{
    public:
        Spikey();
};
