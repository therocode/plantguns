#include "weaponfactory.hpp"

std::unique_ptr<Weapon> weaponFactory(WeaponType type, const std::unordered_map<std::string, fea::Texture>& textures)
{
    if(type == PISTOL)
        return std::unique_ptr<Weapon>(new Pistol(textures));
    else if(type == SHOTGUN)
        return std::unique_ptr<Weapon>(new Shotgun(textures));
    else
        return nullptr;
}
