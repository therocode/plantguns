#pragma once
#include <unordered_map>
#include <fea/render2d.hpp>
#include "player.hpp"
#include "enemies.hpp"
#include "plant.hpp"
#include "pickup.hpp"

class Level
{
    public:
        Level();
        void renderMe(fea::Renderer2D& renderer);
        void setTextures(const std::unordered_map<std::string, fea::Texture>& textures);
        void plant(Player& player);
        void update(Player& player);
        void spawn(EnemyType type, const glm::vec2& position);
    private:
        void setTile(const glm::uvec2& tile, int32_t id);
        int32_t getTile(const glm::uvec2& tile) const;
        void createPlant(const glm::uvec2& tile, int32_t id);
        bool hasPlant(const glm::uvec2& tile) const;
        bool plantRipe(const glm::uvec2& tile) const;
        int32_t plantId(const glm::uvec2& tile) const;
        void destroyPlant(const glm::uvec2& tile);
        void createPickupFromPlant(const glm::uvec2& tile);
        fea::TileMap mTiles;
        std::array<int32_t, 40 * 24> mTileIds;
        const std::unordered_map<std::string, fea::Texture>* mTextures;
        std::unordered_map<glm::uvec2, Plant> mPlants;
        std::unordered_map<glm::uvec2, Pickup> mPickups;
        std::vector<std::unique_ptr<Bullet>> mBullets;
        std::vector<std::unique_ptr<Enemy>> mEnemies;
};
