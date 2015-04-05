#pragma once
#include <array>
#include <cstdint>
#include <glm/glm.hpp>

enum TileType {GRASS, PLOT, FENCEH, FENCEV, FENCETL, FENCETR, FENCEBR, FENCEBL};

using TileMap = std::array<TileType, 40 * 24>;

TileType getTile(const TileMap& tilemap, const glm::uvec2& tile);
