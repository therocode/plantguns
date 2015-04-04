#include "level.hpp"
#include "texturemaker.hpp"
        
enum TileType {GRASS, PLOT, FENCEH, FENCEV};

Level::Level():
    mTiles(40, 24, 32, 32, 0.5f, 0.5f)
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

void Level::update(Player& player)
{
    for(auto& plant : mPlants)
        plant.second.update();

    glm::vec2 playerCollStart = player.position() + glm::vec2(12.0f, 12.0f);
    glm::vec2 playerCollEnd = playerCollStart + glm::vec2(8.0f, 8.0f);

    std::vector<glm::uvec2> toPickup;


    for(auto& pickup : mPickups)
    {
        glm::vec2 pickupCollStart = (glm::vec2) pickup.first * 32.0f;
        glm::vec2 pickupCollEnd = pickupCollStart + glm::vec2(32.0f, 32.0f);


        if(playerCollStart.x < pickupCollEnd.x &&
           playerCollStart.y < pickupCollEnd.y &&
           playerCollEnd.x > pickupCollStart.x &&
           playerCollEnd.y > pickupCollStart.y)
        {
            toPickup.push_back(pickup.first);
        }
    }

    for(uint32_t i = 0; i < mBullets.size();)
    {
        auto& bullet = mBullets[i];
        bullet->update();

        if(bullet->isDead())
            mBullets.erase(mBullets.begin() + i);
        else
            i++;
    }

    for(auto& pickedUp : toPickup)
    {
        mPickups.erase(pickedUp);
    }

    if(player.weapon() != nullptr)
    {
        for(auto& bullet : player.weapon()->getBullets(player.position() + glm::vec2(16.0f, 16.0f)))
        {
            mBullets.push_back(std::move(bullet));
        }
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
