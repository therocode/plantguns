#pragma once
#include <glm/glm.hpp>
#include "tilemap.hpp"

class TilePathAdaptor
{
    public:
        TilePathAdaptor(const TileMap& map);
        const glm::uvec2 getNeighbor(const glm::uvec2& tile, uint32_t index) const;
        uint32_t getNeighborAmount(const glm::uvec2& tile) const;
        int32_t getStepCost(const glm::uvec2& tileA, const glm::uvec2& tileB) const;
        int32_t estimateDistance(const glm::uvec2& start, const glm::uvec2& target) const;
    private:
        bool isSolid(TileType type) const;
        const TileMap& mMap;
};
