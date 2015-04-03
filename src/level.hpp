#pragma once
#include <unordered_map>
#include <fea/render2d.hpp>
#include "player.hpp"
#include "plant.hpp"

class Level
{
    public:
        Level();
        void renderMe(fea::Renderer2D& renderer);
        void setTexture(fea::Texture& texture);
        void plant(Player& player);
        void setPlantTexture(fea::Texture& plantTexture);
    private:
        void setTile(const glm::uvec2& tile, int32_t id);
        int32_t getTile(const glm::uvec2& tile) const;
        void createPlant(const glm::uvec2& tile, int32_t id);
        fea::TileMap mTiles;
        std::array<int32_t, 40 * 24> mTileIds;
        std::unordered_map<glm::uvec2, Plant> mPlants;
        fea::Texture* mPlantTexture;
};
