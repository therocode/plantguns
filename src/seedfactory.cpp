#include "seedfactory.hpp"
#include <iostream>

SeedBag seedFactory(WeaponType type)
{
    SeedBag bag;
    bag.type = type;

    if(type == PISTOL)
    {
        bag.name = "Pistol seed";
        bag.amount = 4;
    }
    else if(type == SHOTGUN)
    {
        bag.name = "Shotgun seed";
        bag.amount = 2;
    }
    else
    {
        std::cout << "invalid bag\n";
    }

    return bag;
}
