#include "plant.hpp"
#include "enemies.hpp"

Plant::Plant(WeaponType id):
    mRipeTimer(2400),
    mId(id)
{
    mHealth = 240;
}

void Plant::setDoneTexture(const fea::Texture& doneTexture)
{
    mDoneTexture = &doneTexture;
}

void Plant::update(bool storm)
{
    Entity::update();

    if(mRipeTimer > 0)
    {
        mRipeTimer -= storm ? 2 : 5;

        if(mRipeTimer <= 0)
        {
            setTexture(*mDoneTexture);
        }
    }
}

bool Plant::isRipe() const
{
    return mRipeTimer <= 0;
}

WeaponType Plant::id() const
{
    return mId;
}

void Plant::trampled(Enemy& enemy)
{
    --mHealth;
}
