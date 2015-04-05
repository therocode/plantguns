#pragma once
#include <array>
#include <cstdint>
#include <glm/glm.hpp>

using TileMap = std::array<int32_t, 40 * 24>;

int32_t getTile(const TileMap& tilemap, const glm::uvec2& tile);
