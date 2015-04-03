#pragma once
#include "entity.hpp"
#include "directionresolver.hpp"

enum Direction{LEFT, RIGHT, UP, DOWN};

class Player : public Entity
{
    public:
        Player();
        void addMove(Direction d);
        void delMove(Direction d);
        virtual void update() override;
    private:
        DirectionResolver mDirectionResolver;
};
