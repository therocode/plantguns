#include "tilepathadaptor.hpp"
#include <iostream>
#include <cstdlib>

TilePathAdaptor::TilePathAdaptor(const TileMap& map) :
    mMap(map)
{
}

const glm::uvec2 TilePathAdaptor::getNeighbor(const glm::uvec2& tile, uint32_t index) const
{
    uint32_t skip = index;

    glm::uvec2 up = glm::uvec2(0, -1);
    if(!isSolid(getTile(mMap, tile + up)))
    {
        if(skip == 0)
            return tile + up;
        --skip;
    }
    
    glm::uvec2 right = glm::uvec2(1, 0);
    if(!isSolid(getTile(mMap, tile + right)))
    {
        if(skip == 0)
            return tile + right;
        --skip;
    }

    glm::uvec2 down = glm::uvec2(0, 1);
    if(!isSolid(getTile(mMap, tile + down)))
    {
        if(skip == 0)
            return tile + down;
        --skip;
    }
    
    glm::uvec2 left = glm::uvec2(-1, 0);
    if(!isSolid(getTile(mMap, tile + left)))
    {
        if(skip == 0)
            return tile + left;
        --skip;
    }

    std::cout << "woops this should'mnt have happened\n";
    exit(2);

    return glm::uvec2();
}

uint32_t TilePathAdaptor::getNeighborAmount(const glm::uvec2& tile) const
{
    uint32_t amount = 0;

    glm::uvec2 up = glm::uvec2(0, -1);
    if(!isSolid(getTile(mMap, tile + up)))
        amount++;

    glm::uvec2 right = glm::uvec2(1, 0);
    if(!isSolid(getTile(mMap, tile + right)))
        amount++;

    glm::uvec2 down = glm::uvec2(0, 1);
    if(!isSolid(getTile(mMap, tile + down)))
        amount++;
    
    glm::uvec2 left = glm::uvec2(-1, 0);
    if(!isSolid(getTile(mMap, tile + left)))
        amount++;

    return amount;
}

int32_t TilePathAdaptor::getStepCost(const glm::uvec2& tileA, const glm::uvec2& tileB) const
{
    return 1;
}

int32_t TilePathAdaptor::estimateDistance(const glm::uvec2& start, const glm::uvec2& target) const
{
    return glm::distance((glm::vec2)start, (glm::vec2)target) * 10.0f;
}

bool TilePathAdaptor::isSolid(TileType type) const
{
    return type != GRASS && type != PLOT;
}
