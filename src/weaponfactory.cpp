#include "weaponfactory.hpp"

std::unique_ptr<Weapon> weaponFactory(WeaponType type, const std::unordered_map<std::string, fea::Texture>& textures, std::function<void(const std::string&)> soundPlayer)
{
    if(type == PISTOL)
        return std::unique_ptr<Weapon>(new Pistol(textures, soundPlayer));
    else if(type == SHOTGUN)
        return std::unique_ptr<Weapon>(new Shotgun(textures, soundPlayer));
    else
        return nullptr;
}
