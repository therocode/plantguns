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
    mLevel.renderMe(mRenderer);

    if(!mPlayer.isDead())
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
    mTextures.emplace("bullet", makeTexture("data/textures/bullet.png"));
    mTextures.emplace("spikey", makeTexture("data/textures/spikey.png"));
}

void PlantGuns::setupPlayer()
{
    mPlayer.setTexture(mTextures.at("hat"));
    mPlayer.setPosition({550.0f, 450.0f});
    mPlayer.giveWeapon(std::unique_ptr<Weapon>(new Pistol(mTextures)));
}

void PlantGuns::setupLevel()
{
    mLevel.setTextures(mTextures);

    mLevel.spawn(SPIKEY, {450.0f, 120.0f});
    mLevel.spawn(SPIKEY, {510.0f, 130.0f});
    mLevel.spawn(SPIKEY, {490.0f, 170.0f});
    mLevel.spawn(SPIKEY, {420.0f, 125.0f});
    mLevel.spawn(SPIKEY, {451.0f, 120.0f});
    mLevel.spawn(SPIKEY, {511.0f, 130.0f});
    mLevel.spawn(SPIKEY, {491.0f, 170.0f});
    mLevel.spawn(SPIKEY, {421.0f, 125.0f});
    mLevel.spawn(SPIKEY, {450.0f, 121.0f});
    mLevel.spawn(SPIKEY, {510.0f, 131.0f});
    mLevel.spawn(SPIKEY, {490.0f, 171.0f});
    mLevel.spawn(SPIKEY, {420.0f, 126.0f});
    mLevel.spawn(SPIKEY, {451.0f, 121.0f});
    mLevel.spawn(SPIKEY, {511.0f, 131.0f});
    mLevel.spawn(SPIKEY, {491.0f, 171.0f});
    mLevel.spawn(SPIKEY, {421.0f, 126.0f});
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
