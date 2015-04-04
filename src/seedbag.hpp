#pragma once
#include <string>
#include <cstdint>
#include "weapons.hpp"

struct SeedBag
{
    WeaponType type;
    uint32_t amount;
    std::string name;
};
