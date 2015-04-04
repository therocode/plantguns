#include "enemies.hpp"
#include "bullets.hpp"
#include <iostream>
#include "player.hpp"
#include "accelerator.hpp"
    
void Enemy::hit(Bullet& bullet)
{
    mHealth -= bullet.damage();
}

int32_t Enemy::damage() const
{
    return mDamage;
}

void Enemy::update(Player* player, PlantMap& plants)
{
    std::vector<glm::vec2> targets = targetList(player, plants);

    if(targets.size() > 0)
        mTarget = closest(targets);
    else
        mTarget = position();

    Entity::update();
}

std::vector<glm::vec2> Enemy::targetList(Player* player, PlantMap& plants) const
{
    std::vector<glm::vec2> targets;

    if(player)
    {
        targets.push_back(player->center());
    }

    for(auto& plant : plants)
        targets.push_back(plant.second.center());

    return targets;
}

glm::vec2 Enemy::closest(const std::vector<glm::vec2>& targets) const
{
    float smallest = 1000.0f;
    glm::vec2 result;

    for(int32_t i = 0; i < targets.size(); i++)
    {
        float distance = glm::distance(targets[i], center());

        if(distance < smallest)
        {
            result = targets[i];
            smallest = distance;
        }
    }

    return result;
}

Spikey::Spikey()
{
    mQuad.setSize({16.0f, 16.0f});
    mHealth = 15;
    mDamage = 9;
}

void Spikey::update(Player* player, PlantMap& plants)
{
    Enemy::update(player, plants);

    Accelerator accelerator;

    mAcceleration = accelerator.get(mTarget - center(), 2.0f, mVelocity, 0.1f);
}
