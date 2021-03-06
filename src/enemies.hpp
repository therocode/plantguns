#pragma once
#include "tilepathadaptor.hpp"
#include "entity.hpp"
#include "plant.hpp"
#include <fea/util/pathfinder.hpp>

class Bullet;

enum EnemyType {SPIKEY};

class Player;

class Enemy : public Entity
{
    public:
        void hit(Bullet& bullet);
        int32_t damage() const;
        virtual void update(Player* player, PlantMap& plants);
        virtual glm::vec2 getTarget(Player* player, PlantMap& plants);
        virtual std::unique_ptr<WeaponType> drop() const;
    protected:
        std::vector<glm::vec2> targetList(Player* player, PlantMap& plants) const;
        glm::vec2 closest(const std::vector<glm::vec2>& targets) const;
        int32_t mDamage;
        glm::vec2 mTarget;
};

class Spikey : public Enemy
{
    public:
        Spikey();
        virtual void update(Player* player, PlantMap& plants) override;
        virtual bool handleCollision() override;
        virtual glm::vec2 getTarget(Player* player, PlantMap& plants) override;
        virtual std::unique_ptr<WeaponType> drop() const override;
    private:
        bool mUsePathFinding;
        fea::Pathfinder<TilePathAdaptor> mPathfinder;
};
