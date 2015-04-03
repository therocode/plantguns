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
    mInputHandler.setKeyRepeatEnabled(false);

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

    update();

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
            else if(event.key.code == fea::Keyboard::A)
                mPlayer.addMove(LEFT);
            else if(event.key.code == fea::Keyboard::D)
                mPlayer.addMove(RIGHT);
            else if(event.key.code == fea::Keyboard::W)
                mPlayer.addMove(UP);
            else if(event.key.code == fea::Keyboard::S)
                mPlayer.addMove(DOWN);
            else if(event.key.code == fea::Keyboard::F)
            {
                mLevel.plant(mPlayer);
            }
        }
        else if(event.type == fea::Event::KEYRELEASED)
        {
            if(event.key.code == fea::Keyboard::A)
                mPlayer.delMove(LEFT);
            else if(event.key.code == fea::Keyboard::D)
                mPlayer.delMove(RIGHT);
            else if(event.key.code == fea::Keyboard::W)
                mPlayer.delMove(UP);
            else if(event.key.code == fea::Keyboard::S)
                mPlayer.delMove(DOWN);
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
    mTextures.emplace("plant", makeTexture("data/textures/plant.png"));
    mTextures.emplace("appletree", makeTexture("data/textures/appletree.png"));
    mTextures.emplace("goldplate", makeTexture("data/textures/goldplate.png"));
}

void PlantGuns::setupPlayer()
{
    mPlayer.setTexture(mTextures.at("hat"));
    mPlayer.setPosition({550.0f, 450.0f});
}

void PlantGuns::setupLevel()
{
    mLevel.setTextures(mTextures);
}

void PlantGuns::update()
{
    mPlayer.update();
    mLevel.update(mPlayer);
}
