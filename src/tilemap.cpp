#include "tilemap.hpp"

TileType getTile(const TileMap& tilemap, const glm::uvec2& tile)
{
    if(tile.x > 39 || tile.y > 23)
        return FENCEH;

    return tilemap[tile.x + tile.y * 40];
}
