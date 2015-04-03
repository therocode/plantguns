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

    //16, 9 corner
    
    //top fences
    mTiles.setTile({17, 9}, FENCEH);
    mTiles.setTile({18, 9}, FENCEH);
    mTiles.setTile({21, 9}, FENCEH);
    mTiles.setTile({22, 9}, FENCEH);

    //left fences
    mTiles.setTile({16, 10}, FENCEV);
    mTiles.setTile({16, 11}, FENCEV);
    mTiles.setTile({16, 14}, FENCEV);
    mTiles.setTile({16, 15}, FENCEV);
    
    //bottom fences
    mTiles.setTile({17, 16}, FENCEH);
    mTiles.setTile({18, 16}, FENCEH);
    mTiles.setTile({21, 16}, FENCEH);
    mTiles.setTile({22, 16}, FENCEH);

    //left fences
    mTiles.setTile({23, 10}, FENCEV);
    mTiles.setTile({23, 11}, FENCEV);
    mTiles.setTile({23, 14}, FENCEV);
    mTiles.setTile({23, 15}, FENCEV);

    //tl plots
    mTiles.setTile({17,10}, PLOT);
    mTiles.setTile({18,10}, PLOT);
    mTiles.setTile({17,11}, PLOT);
    mTiles.setTile({18,11}, PLOT);

    //tr plots
    mTiles.setTile({21,10}, PLOT);
    mTiles.setTile({22,10}, PLOT);
    mTiles.setTile({21,11}, PLOT);
    mTiles.setTile({22,11}, PLOT);

    //bl plots
    mTiles.setTile({17,14}, PLOT);
    mTiles.setTile({18,14}, PLOT);
    mTiles.setTile({17,15}, PLOT);
    mTiles.setTile({18,15}, PLOT);

    //br plots
    mTiles.setTile({21,14}, PLOT);
    mTiles.setTile({22,14}, PLOT);
    mTiles.setTile({21,15}, PLOT);
    mTiles.setTile({22,15}, PLOT);
}

void Level::renderMe(fea::Renderer2D& renderer)
{
    for(const auto& chunk : mTiles.getTileChunks())
        renderer.queue(*chunk);
}

void Level::setTexture(fea::Texture& texture)
{
    mTiles.setTexture(texture);
}
