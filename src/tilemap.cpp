#include "tilemap.hpp"

TileType getTile(const TileMap& tilemap, const glm::uvec2& tile)
{
    return tilemap[tile.x + tile.y * 40];
}
