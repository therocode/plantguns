#include "pickup.hpp"

Pickup::Pickup(WeaponType id):
    mId(id)
{
    mCollisionSize = glm::vec2(32.0f, 32.0f);
}

WeaponType Pickup::id() const
{
    return mId;
}
