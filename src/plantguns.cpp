#include "plantguns.hpp"
#include "texturemaker.hpp"

PlantGuns::PlantGuns():
     mInputHandler(new fea::SDL2InputBackend()),
     mRenderer(fea::Viewport({1280, 768}, {0, 0}, fea::Camera({1280.0f / 2.0f, 768.0f / 2.0f}))),
     mWindow(new fea::SDL2WindowBackend())
{
}

void PlantGuns::setup(const std::vector<std::string>& args)
{
    mWindow.create(fea::VideoMode(1280, 768), "Plant guns");
    mWindow.setFramerateLimit(60);

    mRenderer.setup();

    setupGraphics();
    setupPlayer();
    setupLevel();
}

void PlantGuns::destroy()
{
    mWindow.close();
}

void PlantGuns::loop()
{
    handleInput();
    mRenderer.clear();
    render();

    mWindow.swapBuffers();
}

void PlantGuns::handleInput()
{
    fea::Event event;

    while(mInputHandler.pollEvent(event))
    {
        if(event.type == fea::Event::CLOSED)
        {
            quit();
        }
        else if(event.type == fea::Event::KEYPRESSED)
        {
            if(event.key.code == fea::Keyboard::ESCAPE)
                quit();
        }
    }
}
        
void PlantGuns::render()
{
    mLevel.renderMe(mRenderer);
    mPlayer.renderMe(mRenderer);

    mRenderer.render();
}

void PlantGuns::setupGraphics()
{
    mTextures.emplace("hat", makeTexture("data/textures/hat.png"));
    mTextures.emplace("tiles", makeTexture("data/textures/tiles.png"));
}

void PlantGuns::setupPlayer()
{
    mPlayer.setTexture(mTextures.at("hat"));
    mPlayer.setPosition({550.0f, 450.0f});
}

void PlantGuns::setupLevel()
{
    mLevel.setTexture(mTextures.at("tiles"));
}
