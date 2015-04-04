#pragma once
#include "entity.hpp"
#include "weapons.hpp"

class Pickup : public Entity
{
    public:
        Pickup(WeaponType id);
        WeaponType id() const;
    private:
        WeaponType mId;
};
