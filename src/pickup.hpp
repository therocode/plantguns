#pragma once
#include "entity.hpp"

class Pickup : public Entity
{
    public:
        Pickup(int32_t id);
    private:
        int32_t mId;
};
