#include "plantguns.hpp"
#include "texturemaker.hpp"
#include "seedfactory.hpp"

PlantGuns::PlantGuns():
     mInputHandler(new fea::SDL2InputBackend()),
     mRenderer(fea::Viewport({1280, 768}, {0, 0}, fea::Camera({1280.0f / 2.0f, 768.0f / 2.0f}))),
     mWindow(new fea::SDL2WindowBackend()),
     mLevel(mPlayer)
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
            else if(event.key.code == fea::Keyboard::J)
                mPlayer.addFire(LEFT);
            else if(event.key.code == fea::Keyboard::L)
                mPlayer.addFire(RIGHT);
            else if(event.key.code == fea::Keyboard::I)
                mPlayer.addFire(UP);
            else if(event.key.code == fea::Keyboard::K)
                mPlayer.addFire(DOWN);
            else if(event.key.code == fea::Keyboard::H)
            {
                if(!mPlayer.isDead())
                    mLevel.plant(mPlayer);
            }
            else if(event.key.code == fea::Keyboard::O)
            {
                mPlayer.toggleWeapon();
            }
            else if(event.key.code == fea::Keyboard::U)
            {
                mPlayer.toggleSeed();
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
            else if(event.key.code == fea::Keyboard::J)
                mPlayer.delFire(LEFT);
            else if(event.key.code == fea::Keyboard::L)
                mPlayer.delFire(RIGHT);
            else if(event.key.code == fea::Keyboard::I)
                mPlayer.delFire(UP);
            else if(event.key.code == fea::Keyboard::K)
                mPlayer.delFire(DOWN);
        }
    }
}
        
void PlantGuns::render()
{
    mLevel.renderMe(mRenderer, mPlayer);

    mRenderer.render();
}

void PlantGuns::setupGraphics()
{
    mTextures.emplace("hat", makeTexture("data/textures/hat.png"));
    mTextures.emplace("tiles", makeTexture("data/textures/tiles.png"));
    mTextures.emplace("plant", makeTexture("data/textures/plant.png"));
    mTextures.emplace("appletree", makeTexture("data/textures/appletree.png"));
    mTextures.emplace("bullet", makeTexture("data/textures/bullet.png"));
    mTextures.emplace("spikey", makeTexture("data/textures/spikey.png"));
    mTextures.emplace("rain", makeTexture("data/textures/rain.png"));
    mTextures.emplace("minibullet", makeTexture("data/textures/minibullet.png"));
    mTextures.emplace("health", makeTexture("data/textures/health.png"));
    mTextures.emplace("gun", makeTexture("data/textures/gun.png"));
    mTextures.emplace("shotgun", makeTexture("data/textures/shotgun.png"));
}

void PlantGuns::setupPlayer()
{
    mPlayer.setTexture(mTextures.at("hat"));
    mPlayer.setPosition({550.0f, 450.0f});
    mPlayer.giveWeapon(std::unique_ptr<Weapon>(new Pistol(mTextures)));
    mPlayer.giveWeapon(std::unique_ptr<Weapon>(new Shotgun(mTextures)));
    mPlayer.giveSeeds(seedFactory(PISTOL));
    mPlayer.giveSeeds(seedFactory(SHOTGUN));
}

void PlantGuns::setupLevel()
{
    mLevel.setTextures(mTextures);
}

void PlantGuns::update()
{
    if(!mPlayer.isDead())
    {
        mLevel.update(&mPlayer);
        mPlayer.update();
    }
    else
        mLevel.update(nullptr);

}
