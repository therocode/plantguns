#include "plant.hpp"

Plant::Plant(int32_t id):
    mRipeTimer(120),
    mId(id)
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

int32_t Plant::id() const
{
    return mId;
}
