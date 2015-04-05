#include "level.hpp"
#include "texturemaker.hpp"
#include "intersector.hpp"
#include "seedfactory.hpp"
#include "weaponfactory.hpp"
#include <random>

const uint32_t stormLength = 600;
const uint32_t healAmount = 20;

Level::Level(Player& player):
    mTiles(40, 24, 32, 32, 0.33333333f, 0.33333333f),
    mStormTimer(stormLength),
    mStorms(false),
    mRainTargetOpacity(0.0f),
    mLightning({1280.0f, 768.0f}),
    mLightningTargetOpacity(0.0f) 
{
    player.setCollisionMap(mTileIds);

    mRainAnimation = fea::Animation(glm::vec2(0.0f / 128.0f, 0.0f / 32.0f), glm::vec2(32.0f / 128.0f, 32.0f / 32.0f), 4, 7);

    mRain = fea::RepeatedQuad({1280.0f, 768.0f});
    mRain.setTileSize(glm::vec2({64.0f, 64.0f}));
    mRain.setScrollSpeed(glm::vec2({-0.01f, 0.06f}));
    mRain.setAnimation(mRainAnimation);
    mRain.setOpacity(0.0f);
    mLightning.setOpacity(0.0f);

    mFont = std::unique_ptr<fea::Font>(new fea::Font("data/fonts/LiberationSans-Regular.ttf", 14));
    mTimerText.setPenFont(*mFont);
    mTimerText.setPenColor(fea::Color::White);
    mTimerText.setColor(fea::Color::White);
    mInfoText.setPenFont(*mFont);
    mInfoText.setPenColor(fea::Color::White);
    mInfoText.setColor(fea::Color::White);

    mTiles.addTileDefinition(GRASS, fea::TileDefinition(glm::uvec2(0, 0)));
    mTiles.addTileDefinition(PLOT, fea::TileDefinition(glm::uvec2(1, 0)));
    mTiles.addTileDefinition(FENCEH, fea::TileDefinition(glm::uvec2(0, 1)));
    mTiles.addTileDefinition(FENCEV, fea::TileDefinition(glm::uvec2(1, 1)));
    mTiles.addTileDefinition(FENCETL, fea::TileDefinition(glm::uvec2(2, 2)));
    mTiles.addTileDefinition(FENCETR, fea::TileDefinition(glm::uvec2(1, 2)));
    mTiles.addTileDefinition(FENCEBL, fea::TileDefinition(glm::uvec2(2, 1)));
    mTiles.addTileDefinition(FENCEBR, fea::TileDefinition(glm::uvec2(0, 2)));

    mTiles.fill(GRASS);
    mTileIds.fill(GRASS);

    //16, 9 corner
    
    //top fences
    setTile({17, 9}, FENCEH);
    setTile({18, 9}, FENCEH);
    setTile({21, 9}, FENCEH);
    setTile({22, 9}, FENCEH);

    //left fences
    setTile({16, 10}, FENCEV);
    setTile({16, 11}, FENCEV);
    setTile({16, 14}, FENCEV);
    setTile({16, 15}, FENCEV);
    
    //bottom fences
    setTile({17, 16}, FENCEH);
    setTile({18, 16}, FENCEH);
    setTile({21, 16}, FENCEH);
    setTile({22, 16}, FENCEH);

    //left fences
    setTile({23, 10}, FENCEV);
    setTile({23, 11}, FENCEV);
    setTile({23, 14}, FENCEV);
    setTile({23, 15}, FENCEV);

    //corner fences
    setTile({16, 9}, FENCETL);
    setTile({23, 9}, FENCETR);
    setTile({16, 16}, FENCEBL);
    setTile({23, 16}, FENCEBR);

    //tl plots
    setTile({17,10}, PLOT);
    setTile({18,10}, PLOT);
    setTile({17,11}, PLOT);
    setTile({18,11}, PLOT);

    //tr plots
    setTile({21,10}, PLOT);
    setTile({22,10}, PLOT);
    setTile({21,11}, PLOT);
    setTile({22,11}, PLOT);

    //bl plots
    setTile({17,14}, PLOT);
    setTile({18,14}, PLOT);
    setTile({17,15}, PLOT);
    setTile({18,15}, PLOT);

    //br plots
    setTile({21,14}, PLOT);
    setTile({22,14}, PLOT);
    setTile({21,15}, PLOT);
    setTile({22,15}, PLOT);
}

void Level::renderMe(fea::Renderer2D& renderer, Player& player)
{
    for(const auto& chunk : mTiles.getTileChunks())
        renderer.queue(*chunk);

    for(auto& plant : mPlants)
        plant.second.renderMe(renderer);

    for(auto& pickup : mPickups)
        pickup.renderMe(renderer);

    for(auto& bullet : mBullets)
        bullet->renderMe(renderer);

    for(auto& enemy : mEnemies)
        enemy->renderMe(renderer);

    if(!player.isDead())
        player.renderMe(renderer);

    renderer.queue(mRain);
    mRain.tick();

    renderer.queue(mLightning);

    renderer.queue(mTimerText);
    renderer.queue(mInfoText);
}

void Level::setTextures(const std::unordered_map<std::string, fea::Texture>& textures)
{
    mTextures = &textures;

    mTiles.setTexture(mTextures->at("tiles"));
    mRain.setTexture(textures.at("rain"));
}

void Level::plant(Player& player, std::function<void(const std::string&)> soundPlayer)
{
    glm::uvec2 plantTile = (glm::uvec2)((player.position() + glm::vec2({16.0f, 16.0f})) / 32.0f);

    int32_t tileId = getTile(plantTile);

    if(tileId == PLOT)
    {
        if(!hasPlant(plantTile))
        {
            SeedBag* seedBag = player.seedBag();

            if(seedBag)
            {
                createPlant(plantTile, seedBag->type);
                soundPlayer("shovel");
                player.usedSeed();
            }
        }
        else
        {
            if(plantRipe(plantTile))
            {
                auto weapon = weaponFactory(plantId(plantTile), *mTextures, soundPlayer);
                std::string name = weapon->name();
                player.giveWeapon(std::move(weapon));
                destroyPlant(plantTile);
                mTextEntries.push_back({name, player.position(), 60});
            }
        }
    }
}

void Level::update(Player* player, std::function<void(const std::string&)> soundPlayer)
{
    Intersector intersector;

    std::vector<glm::uvec2> plantsToRemove;

    for(auto& plant : mPlants)
    {
        plant.second.update(mStorms);

        if(plant.second.isDead())
        {
            plantsToRemove.push_back(plant.first);
        }
    }

    for(auto& plantTile : plantsToRemove)
        destroyPlant(plantTile);

    if(player)
    {
        std::vector<glm::uvec2> toPickup;

        for(uint32_t i = 0; i < mPickups.size();)
        {
            auto& pickup = mPickups[i];
            if(intersector.intersects(*player, pickup))
            {
                soundPlayer("pickup");
                if(pickup.id() == HEALTH)
                    player->heal(healAmount);
                else
                    player->giveSeeds(seedFactory(pickup.id()));

                mPickups.erase(mPickups.begin() + i);
            }
            else
            {
                ++i;
            }
        }
    }

    for(uint32_t i = 0; i < mBullets.size();)
    {
        auto& bullet = mBullets[i];
        bullet->update();

        bool dead = false;

        for(auto& enemy : mEnemies)
        {
            if(intersector.intersects(*bullet, *enemy))
            {
                enemy->hit(*bullet);
                enemy->knockFrom(bullet->center(), 6.5f);
                enemy->colorize(orangeHurtColor);
                soundPlayer("metallic");
                dead = true;
            }
        }

        if(bullet->isDead() || dead)
            mBullets.erase(mBullets.begin() + i);
        else
            i++;
    }

    for(uint32_t i = 0; i < mEnemies.size();)
    {
        auto& enemy = mEnemies[i];
        enemy->update(player, mPlants);

        if(player)
        {
            if(intersector.intersects(*player, *enemy))
            {
                soundPlayer("grunt");
                player->hit(*enemy);
            }
        }

        for(uint32_t j = i+1; j < mEnemies.size(); j++)
        {
            auto& other = mEnemies[j];
            if(intersector.intersects(*enemy, *other))
            {
                enemy->knockFrom(other->center(), 1.5f);
                other->knockFrom(enemy->center(), 1.5f);
            }
        }

        for(auto& plant : mPlants)
        {
            if(intersector.intersects(*enemy, plant.second))
            {
                plant.second.trampled(*enemy);
            }
        }

        if(enemy->isDead())
        {
            soundPlayer("squash");
            auto drop = enemy->drop();
            if(drop)
                createPickupFromEnemy(*enemy, *drop);
            mEnemies.erase(mEnemies.begin() + i);
        }
        else
            i++;
    }

    if(player)
    {
        if(player->weapon() != nullptr)
        {
            for(auto& bullet : player->weapon()->getBullets(player->position() + glm::vec2(16.0f, 16.0f), *player))
            {
                bullet->setCollisionMap(mTileIds);
                mBullets.push_back(std::move(bullet));
            }
        }
    }

    if(mStorms)
    {
        std::random_device rd;
        std::uniform_int_distribution<> randomPercent(0, 99);

        if(randomPercent(rd) < 2)
        {
            glm::vec2 location = spawnLocation();
            spawn(SPIKEY, location);
        }

        if(randomPercent(rd) < 1 && !mLightningOn)
        {
            if(randomPercent(rd) < 50)
            {
                mLightningOn = 5;
                mLightningTargetOpacity = 0.5f;
            }
        }
    }

    if(mLightningOn > 0)
    {
        --mLightningOn;

        if(mLightningOn == 0)
        {
            mLightningTargetOpacity = 0.0f;
        }
    }

    if(mStormTimer > 0)
        --mStormTimer;
    else
    {
        mStormTimer = stormLength;

        if(mStorms)
        {//it is now sunny
            mRainTargetOpacity = 0.0f;
            mLightningOn = false;
            soundPlayer("stop");
        }
        else
        {//it is now a storm
            mRainTargetOpacity = 1.0f;
            soundPlayer("storm");
        }

        mStorms = !mStorms;
    }

    updateTimer();

    if(player)
        updatePlayerInfo(*player);

    float currentOpacity = mRain.getOpacity();
    if(currentOpacity < mRainTargetOpacity - 0.02f)
        mRain.setOpacity(currentOpacity + 0.01f);
    else if(currentOpacity > mRainTargetOpacity + 0.02f)
        mRain.setOpacity(currentOpacity - 0.01f);

    currentOpacity = mLightning.getOpacity();
    if(currentOpacity < mLightningTargetOpacity - 0.01f)
        mLightning.setOpacity(currentOpacity + 0.15f);
    else if(currentOpacity > mLightningTargetOpacity + 0.01f)
        mLightning.setOpacity(currentOpacity - 0.15f);
}

void Level::spawn(EnemyType type, const glm::vec2& position)
{
    if(type == SPIKEY)
    {
        std::unique_ptr<Spikey> spikey = std::unique_ptr<Spikey>(new Spikey());
        spikey->setPosition(position);
        spikey->setTexture(mTextures->at("spikey"));
        spikey->setCollisionMap(mTileIds);
        mEnemies.push_back(std::move(spikey));
    }
}

void Level::setTile(const glm::uvec2& tile, TileType id)
{
    mTileIds[tile.x + tile.y * 40] = id;
    mTiles.setTile(tile, id);
}

TileType Level::getTile(const glm::uvec2& tile) const
{
    return mTileIds[tile.x + tile.y * 40];
}

void Level::createPlant(const glm::uvec2& tile, WeaponType id)
{
    Plant plant(id);

    plant.setTexture(mTextures->at("plant"));
    plant.setDoneTexture(mTextures->at("appletree"));
    plant.setPosition(((glm::vec2)tile) * 32.0f);
    mPlants.emplace(tile, std::move(plant)); 
}

bool Level::hasPlant(const glm::uvec2& tile) const
{
    return mPlants.count(tile) != 0;
}

bool Level::plantRipe(const glm::uvec2& tile) const
{
    if(hasPlant(tile))
    {
        return mPlants.at(tile).isRipe();
    }

    return false;
}

WeaponType Level::plantId(const glm::uvec2& tile) const
{
    return mPlants.at(tile).id();
}

void Level::destroyPlant(const glm::uvec2& tile)
{
    mPlants.erase(tile);
}

void Level::createPickupFromEnemy(const Enemy& enemy, WeaponType type)
{
    Pickup pickup(type);
    if(type == HEALTH)
        pickup.setTexture(mTextures->at("health"));
    else if(type == PISTOL)
        pickup.setTexture(mTextures->at("gun"));
    else if(type == SHOTGUN)
        pickup.setTexture(mTextures->at("shotgun"));

    pickup.setPosition(enemy.center() - pickup.size() / 2.0f);
    mPickups.push_back(std::move(pickup));
}

glm::vec2 Level::spawnLocation() const
{
    glm::uvec2 tile;
    std::random_device rd;
    std::uniform_int_distribution<> directionRand(0, 3);
    std::uniform_int_distribution<> xTile(0, 39);
    std::uniform_int_distribution<> yTile(0, 23);

    int32_t direction = directionRand(rd);

    if(direction == 0)
        tile = glm::vec2(0, yTile(rd));
    else if(direction == 1)
        tile = glm::vec2(39, yTile(rd));
    else if(direction == 2)
        tile = glm::vec2(xTile(rd), 23);
    else if(direction == 3)
        tile = glm::vec2(xTile(rd), 0);

    return (glm::vec2)tile * 32.0f;
}

void Level::updateTimer()
{
    mTimerText.setPenPosition({640.0f - mTimerText.getSize().x / 2.0f, 100.0f});
    mTimerText.clear();
    mTimerText.write("Storm " + (mStorms ? std::string("ends") : std::string("starts")) + " in: " + std::to_string(mStormTimer / 60));
}

void Level::updatePlayerInfo(Player& player)
{
    auto* weapon = player.weapon();
    std::string weaponName = "No weapons";
    std::string weaponAmmo;
    if(weapon)
    {
        weaponName = weapon->name();
        weaponAmmo = std::to_string(weapon->ammo());
    }

    auto* seedBag = player.seedBag();
    std::string seedName = "No seeds";
    std::string seedAmount;
    if(seedBag)
    {
        seedName = seedBag->name;
        seedAmount = std::to_string(seedBag->amount);
    }

    mInfoText.setPenPosition({100.0f, 484.0f});
    mInfoText.clear();
    mInfoText.write("Health: " + std::to_string(player.health()));
    mInfoText.setPenPosition({100.0f, 510.0f});
    mInfoText.write(weaponName + ": " + weaponAmmo);
    mInfoText.setPenPosition({100.0f, 536.0f});
    mInfoText.write(seedName + ": " + seedAmount);

    for(uint32_t i = 0; i < mTextEntries.size();)
    {
        auto& text = mTextEntries[i];

        mInfoText.setPenPosition(text.position + glm::vec2(-20.0f, -20.0f));
        mInfoText.write(text.text);

        if(--text.ttl == 0)
        {
            mTextEntries.erase(mTextEntries.begin() + i);
        }
        else
        {
            ++i;
        }
    }
}
