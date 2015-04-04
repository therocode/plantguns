#include "level.hpp"
#include "texturemaker.hpp"
#include "intersector.hpp"
#include <random>
        
enum TileType {GRASS, PLOT, FENCEH, FENCEV};

const uint32_t stormLength = 600;

Level::Level():
    mTiles(40, 24, 32, 32, 0.5f, 0.5f),
    mStormTimer(stormLength),
    mStorms(false)
{
    mTiles.addTileDefinition(GRASS, fea::TileDefinition(glm::uvec2(0, 0)));
    mTiles.addTileDefinition(PLOT, fea::TileDefinition(glm::uvec2(1, 0)));
    mTiles.addTileDefinition(FENCEH, fea::TileDefinition(glm::uvec2(0, 1)));
    mTiles.addTileDefinition(FENCEV, fea::TileDefinition(glm::uvec2(1, 1)));

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

void Level::renderMe(fea::Renderer2D& renderer)
{
    for(const auto& chunk : mTiles.getTileChunks())
        renderer.queue(*chunk);

    for(auto& plant : mPlants)
        plant.second.renderMe(renderer);

    for(auto& pickup : mPickups)
        pickup.second.renderMe(renderer);

    for(auto& bullet : mBullets)
        bullet->renderMe(renderer);

    for(auto& enemy : mEnemies)
        enemy->renderMe(renderer);
}

void Level::setTextures(const std::unordered_map<std::string, fea::Texture>& textures)
{
    mTextures = &textures;

    mTiles.setTexture(mTextures->at("tiles"));
}

void Level::plant(Player& player)
{
    glm::uvec2 plantTile = (glm::uvec2)((player.position() + glm::vec2({16.0f, 16.0f})) / 32.0f);

    int32_t tileId = getTile(plantTile);

    if(tileId == PLOT)
    {
        if(!hasPlant(plantTile))
        {
            createPlant(plantTile, player.plantId());
        }
        else
        {
            if(plantRipe(plantTile))
            {
                createPickupFromPlant(plantTile);
                destroyPlant(plantTile);
            }
        }
    }
}

void Level::update(Player* player)
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
        glm::vec2 playerCollStart = player->position() + glm::vec2(12.0f, 12.0f);
        glm::vec2 playerCollSize = glm::vec2(8.0f, 8.0f);

        std::vector<glm::uvec2> toPickup;


        for(auto& pickup : mPickups)
        {
            glm::vec2 pickupCollStart = (glm::vec2) pickup.first * 32.0f;
            glm::vec2 pickupCollSize = glm::vec2(32.0f, 32.0f);

            if(intersector.intersects(playerCollStart, playerCollSize, pickupCollStart, pickupCollSize))
            {
                toPickup.push_back(pickup.first);
            }
        }

        for(auto& pickedUp : toPickup)
        {
            mPickups.erase(pickedUp);
        }
    }

    for(uint32_t i = 0; i < mBullets.size();)
    {
        auto& bullet = mBullets[i];
        bullet->update();

        bool dead = false;

        for(auto& enemy : mEnemies)
        {
            if(intersector.intersects(bullet->position(), bullet->size(), enemy->position(), enemy->size()))
            {
                enemy->hit(*bullet);
                enemy->knockFrom(bullet->center(), 6.5f);
                enemy->colorize(orangeHurtColor);
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
            if(intersector.intersects(player->position(), player->size(), enemy->position(), enemy->size()))
            {
                player->hit(*enemy);
            }
        }

        for(uint32_t j = i+1; j < mEnemies.size(); j++)
        {
            auto& other = mEnemies[j];
            if(intersector.intersects(enemy->position(), enemy->size(), other->position(), other->size()))
            {
                enemy->knockFrom(other->center(), 1.5f);
                other->knockFrom(enemy->center(), 1.5f);
            }
        }

        for(auto& plant : mPlants)
        {
            if(intersector.intersects(enemy->position(), enemy->size(), plant.second.position(), plant.second.size()))
            {
                plant.second.trampled(*enemy);
            }
        }

        if(enemy->isDead())
            mEnemies.erase(mEnemies.begin() + i);
        else
            i++;
    }

    if(player)
    {
        if(player->weapon() != nullptr)
        {
            for(auto& bullet : player->weapon()->getBullets(player->position() + glm::vec2(16.0f, 16.0f)))
            {
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
    }

    if(mStormTimer > 0)
        --mStormTimer;
    else
    {
        mStormTimer = stormLength;

        if(mStorms)
        {//it is now sunny
        }
        else
        {//it is now a storm
        }

        mStorms = !mStorms;
    }
}

void Level::spawn(EnemyType type, const glm::vec2& position)
{
    if(type == SPIKEY)
    {
        std::unique_ptr<Spikey> spikey = std::unique_ptr<Spikey>(new Spikey());
        spikey->setPosition(position);
        spikey->setTexture(mTextures->at("spikey"));
        mEnemies.push_back(std::move(spikey));
    }
}

void Level::setTile(const glm::uvec2& tile, int32_t id)
{
    mTileIds[tile.x + tile.y * 40] = id;
    mTiles.setTile(tile, id);
}

int32_t Level::getTile(const glm::uvec2& tile) const
{
    return mTileIds[tile.x + tile.y * 40];
}

void Level::createPlant(const glm::uvec2& tile, int32_t id)
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

int32_t Level::plantId(const glm::uvec2& tile) const
{
    return mPlants.at(tile).id();
}

void Level::destroyPlant(const glm::uvec2& tile)
{
    mPlants.erase(tile);
}

void Level::createPickupFromPlant(const glm::uvec2& tile)
{
    int32_t id = plantId(tile);

    glm::uvec2 spawnTile = tile;

    int32_t random = rand() % 4;
    if(random == 0)
        spawnTile.x += 1;
    else if(random == 1)
        spawnTile.x -= 1;
    else if(random == 2)
        spawnTile.y += 1;
    else if(random == 3)
        spawnTile.y -= 1;

    Pickup pickup(id);
    pickup.setTexture(mTextures->at("goldplate"));
    pickup.setPosition((glm::vec2)(spawnTile) * 32.0f);
    mPickups.emplace(spawnTile, std::move(pickup));
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
