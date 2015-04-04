#pragma once
#include "entity.hpp"

enum EnemyType {SPIKEY};

class Enemy : public Entity
{
    public:
        bool isDead() const;
};

class Spikey : public Enemy
{
    public:
        Spikey();
};
