#include "tilemap.hpp"

int32_t getTile(const TileMap& tilemap, const glm::uvec2& tile)
{
    return tilemap[tile.x + tile.y * 40];
}
