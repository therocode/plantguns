#pragma once
#include <unordered_map>
#include <fea/render2d.hpp>
#include <fea/render2dtext.hpp>
#include "player.hpp"
#include "enemies.hpp"
#include "plant.hpp"
#include "pickup.hpp"
#include <array>
#include "tilemap.hpp"

struct TextEntry
{
    std::string text;
    glm::vec2 position;
    uint32_t ttl;
};

class Level
{
    public:
        Level(Player& player);
        void renderMe(fea::Renderer2D& renderer, Player& player);
        void setTextures(const std::unordered_map<std::string, fea::Texture>& textures);
        void plant(Player& player, std::function<void(const std::string&)> soundPlayer);
        void update(Player* player, std::function<void(const std::string&)> soundPlayer);
        void spawn(EnemyType type, const glm::vec2& position);
    private:
        void setTile(const glm::uvec2& tile, TileType id);
        TileType getTile(const glm::uvec2& tile) const;
        void createPlant(const glm::uvec2& tile, WeaponType id);
        bool hasPlant(const glm::uvec2& tile) const;
        bool plantRipe(const glm::uvec2& tile) const;
        WeaponType plantId(const glm::uvec2& tile) const;
        void destroyPlant(const glm::uvec2& tile);
        void createPickupFromEnemy(const Enemy& enemy, WeaponType type);
        glm::vec2 spawnLocation() const;
        void updateTimer();
        void updatePlayerInfo(Player& player);
        fea::TileMap mTiles;
        TileMap mTileIds;
        const std::unordered_map<std::string, fea::Texture>* mTextures;
        PlantMap mPlants;
        std::vector<Pickup> mPickups;
        std::vector<std::unique_ptr<Bullet>> mBullets;
        std::vector<std::unique_ptr<Enemy>> mEnemies;
        std::vector<TextEntry> mTextEntries;

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
