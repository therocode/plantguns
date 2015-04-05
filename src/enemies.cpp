#include "enemies.hpp"
#include "bullets.hpp"
#include <iostream>
#include "player.hpp"
#include "accelerator.hpp"
#include <random>
    
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
    if(player || plants.size())
    {
        mTarget = getTarget(player, plants);
        Entity::update();
    }
}

glm::vec2 Enemy::getTarget(Player* player, PlantMap& plants)
{
    std::vector<glm::vec2> targets = targetList(player, plants);

    if(targets.size() > 0)
        return closest(targets);
    else
        return center();
}

std::unique_ptr<WeaponType> Enemy::drop() const
{
    return std::unique_ptr<WeaponType>(new WeaponType(HEALTH));
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

Spikey::Spikey():
    mUsePathFinding(false)
{
    mQuad.setSize({16.0f, 16.0f});
    mHealth = 15;
    mDamage = 9;
    mCollisionSize = glm::vec2(16.0f, 16.0f);
}

void Spikey::update(Player* player, PlantMap& plants)
{
    Enemy::update(player, plants);

    Accelerator accelerator;

    mAcceleration = accelerator.get(mTarget - center(), 1.4f, mVelocity, 0.1f);
}

bool Spikey::handleCollision()
{
    mUsePathFinding = true;
    return true;
}

glm::vec2 Spikey::getTarget(Player* player, PlantMap& plants)
{
    if(!mUsePathFinding)
    {
        return Enemy::getTarget(player, plants);
    }
    else
    {
        glm::uvec2 closestTile = (glm::uvec2)(closest(targetList(player, plants)) / 32.0f);
        glm::uvec2 start = (glm::uvec2)(center() / 32.0f);
        
        TilePathAdaptor adaptor(*mCollisionTiles);

        auto path = mPathfinder.findPath(adaptor, start, closestTile);

        if(path.size() > 1)
            return (glm::vec2)(path[1]) * 32.0f + glm::vec2(16.0f, 16.0f);
        else 
            return (glm::vec2)(closestTile) * 32.0f + glm::vec2(16.0f, 16.0f);
    }
}

std::unique_ptr<WeaponType> Spikey::drop() const
{
    std::random_device rd;
    std::uniform_int_distribution<> randomPercent(0, 99);

    if(randomPercent(rd) < 15) // 1/20
    {
        int32_t percent = randomPercent(rd);
        if(percent < 20)
        {
            return std::unique_ptr<WeaponType>(new WeaponType(SHOTGUN));
        }
        else if(percent < 80)
        {
            return std::unique_ptr<WeaponType>(new WeaponType(PISTOL));
        }
        else
        {
            return std::unique_ptr<WeaponType>(new WeaponType(HEALTH));
        }
    }

    return nullptr;
}
