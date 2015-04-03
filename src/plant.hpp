#pragma once
#include "entity.hpp"

class Plant : public Entity
{
    public:
        Plant();
        void setDoneTexture(const fea::Texture& doneTexture);
        void update();
        bool isRipe() const;
    private:
        const fea::Texture* mDoneTexture;
        uint32_t mRipeTimer;
};
