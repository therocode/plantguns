#include "plant.hpp"

Plant::Plant():
    mRipeTimer(1200)
{
}

void Plant::setDoneTexture(const fea::Texture& doneTexture)
{
    mDoneTexture = &doneTexture;
}

void Plant::update()
{
    Entity::update();

    if(mRipeTimer > 0)
    {
        mRipeTimer--;

        if(mRipeTimer == 0)
        {
            setTexture(*mDoneTexture);
        }
    }
}

bool Plant::isRipe() const
{
    return !mRipeTimer;
}
