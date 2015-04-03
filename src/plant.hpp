#pragma once
#include "entity.hpp"

class Plant : public Entity
{
    public:
        Plant(int32_t id);
        void setDoneTexture(const fea::Texture& doneTexture);
        void update();
        bool isRipe() const;
        int32_t id() const;
    private:
        const fea::Texture* mDoneTexture;
        uint32_t mRipeTimer;
        int32_t mId;
};
