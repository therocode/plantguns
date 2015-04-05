#pragma once
#include "weapons.hpp"

std::unique_ptr<Weapon> weaponFactory(WeaponType type, const std::unordered_map<std::string, fea::Texture>& textures, std::function<void(const std::string&)> soundPlayer);
