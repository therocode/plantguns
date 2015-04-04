#pragma once
#include "entity.hpp"

class Enemy;

class Plant : public Entity
{
    public:
        Plant(int32_t id);
        void setDoneTexture(const fea::Texture& doneTexture);
        void update(bool storm);
        bool isRipe() const;
        int32_t id() const;
        void trampled(Enemy& enemy);
    private:
        const fea::Texture* mDoneTexture;
        int32_t mRipeTimer;
        int32_t mId;
};

using PlantMap = std::unordered_map<glm::uvec2, Plant>;
