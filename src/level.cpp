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
}

void Level::setTexture(fea::Texture& texture)
{
    mTiles.setTexture(texture);
}

void Level::plant(Player& player)
{
    glm::uvec2 plantTile = (glm::uvec2)((player.position() + glm::vec2({16.0f, 16.0f})) / 32.0f);

    int32_t tileId = getTile(plantTile);

    if(tileId == PLOT)
    {
        createPlant(plantTile, player.plantId());
    }
}

void Level::setPlantTexture(fea::Texture& plantTexture)
{
    mPlantTexture = &plantTexture;
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
    if(mPlants.count(tile) == 0)
    {
        Plant plant;

        plant.setTexture(*mPlantTexture);
        plant.setPosition(((glm::vec2)tile) * 32.0f);
        mPlants.emplace(tile, std::move(plant)); 
    }
}
