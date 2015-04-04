#include "pickup.hpp"

Pickup::Pickup(WeaponType id):
    mId(id)
{
}

WeaponType Pickup::id() const
{
    return mId;
}
