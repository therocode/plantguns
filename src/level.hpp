#pragma once
#include <unordered_map>
#include <fea/render2d.hpp>
#include <fea/render2dtext.hpp>
#include "player.hpp"
#include "enemies.hpp"
#include "plant.hpp"
#include "pickup.hpp"
#include <array>

class Level
{
    public:
        Level();
        void renderMe(fea::Renderer2D& renderer, Player& player);
        void setTextures(const std::unordered_map<std::string, fea::Texture>& textures);
        void plant(Player& player);
        void update(Player* player);
        void spawn(EnemyType type, const glm::vec2& position);
    private:
        void setTile(const glm::uvec2& tile, int32_t id);
        int32_t getTile(const glm::uvec2& tile) const;
        void createPlant(const glm::uvec2& tile, WeaponType id);
        bool hasPlant(const glm::uvec2& tile) const;
        bool plantRipe(const glm::uvec2& tile) const;
        WeaponType plantId(const glm::uvec2& tile) const;
        void destroyPlant(const glm::uvec2& tile);
        void createPickupFromPlant(const glm::uvec2& tile);
        glm::vec2 spawnLocation() const;
        void updateTimer();
        void updatePlayerInfo(Player& player);
        fea::TileMap mTiles;
        std::array<int32_t, 40 * 24> mTileIds;
        const std::unordered_map<std::string, fea::Texture>* mTextures;
        PlantMap mPlants;
        std::unordered_map<glm::uvec2, Pickup> mPickups;
        std::vector<std::unique_ptr<Bullet>> mBullets;
        std::vector<std::unique_ptr<Enemy>> mEnemies;

        uint32_t mStormTimer;
        bool mStorms;

        std::unique_ptr<fea::Font> mFont;
        fea::TextSurface mTimerText;
        fea::TextSurface mInfoText;

        fea::RepeatedQuad mRain;
        fea::Animation mRainAnimation;
        float mRainTargetOpacity;
        fea::Quad mLightning;
        float mLightningTargetOpacity;
        int32_t mLightningOn;
};
