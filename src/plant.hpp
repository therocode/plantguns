#pragma once
#include "entity.hpp"
#include "weapons.hpp"

class Enemy;

class Plant : public Entity
{
    public:
        Plant(WeaponType id);
        void setDoneTexture(const fea::Texture& doneTexture);
        void update(bool storm);
        bool isRipe() const;
        WeaponType id() const;
        void trampled(Enemy& enemy);
    private:
        const fea::Texture* mDoneTexture;
        int32_t mRipeTimer;
        WeaponType mId;
};

using PlantMap = std::unordered_map<glm::uvec2, Plant>;
