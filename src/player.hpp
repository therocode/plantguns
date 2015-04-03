#pragma once
#include "entity.hpp"
#include "directionresolver.hpp"

enum Direction {LEFT, RIGHT, UP, DOWN};
enum PlantId {PISTOL};

class Player : public Entity
{
    public:
        Player();
        void addMove(Direction d);
        void delMove(Direction d);
        virtual void update() override;
        int32_t plantId() const;
    private:
        DirectionResolver mDirectionResolver;
};
