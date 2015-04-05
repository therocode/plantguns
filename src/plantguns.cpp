#include "plantguns.hpp"
#include "texturemaker.hpp"
#include "seedfactory.hpp"

PlantGuns::PlantGuns():
     mInputHandler(new fea::SDL2InputBackend()),
     mRenderer(fea::Viewport({1280, 768}, {0, 0}, fea::Camera({1280.0f / 2.0f, 768.0f / 2.0f}))),
     mWindow(new fea::SDL2WindowBackend()),
     mLevel(mPlayer),
     mStormGainTarget(0.0f),
     mStormGain(0.0f)
{
}

void PlantGuns::setup(const std::vector<std::string>& args)
{
    mWindow.create(fea::VideoMode(1280, 768), "Plant guns");
    mWindow.setFramerateLimit(60);
    mInputHandler.setKeyRepeatEnabled(false);

    mRenderer.setup();

    setupAudio();
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

void PlantGuns::playAudio(const std::string& name)
{
    if(name == "pistol")
        mAudioPlayer.play(mPistolAudio);
    else if(name == "shotgun")
        mAudioPlayer.play(mShotgunAudio);
    else if(name == "metallic")
        mAudioPlayer.play(mMetallicAudio);
    else if(name == "squash")
        mAudioPlayer.play(mSquashAudio);
    else if(name == "grunt")
        mAudioPlayer.play(mGruntAudio);
    else if(name == "pickup")
        mAudioPlayer.play(mPickupAudio);
    else if(name == "shovel")
        mAudioPlayer.play(mShovelAudio);
    else if(name == "storm")
        mStormGainTarget = 0.7f;
    else if(name == "stop")
        mStormGainTarget = 0.0f;
}

void PlantGuns::handleInput()
{
    fea::Event event;
     std::function<void(const std::string&)> soundPlayer = std::bind(&PlantGuns::playAudio, this, std::placeholders::_1);

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
                    mLevel.plant(mPlayer, soundPlayer);
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

void PlantGuns::setupAudio()
{
    fea::AudioFile file;
    file.open("data/sounds/pistol.ogg");
    mPistolSample.loadSampleData(file);
    mPistolAudio.setSample(mPistolSample);

    file.open("data/sounds/shotgun.ogg");
    mShotgunSample.loadSampleData(file);
    mShotgunAudio.setSample(mShotgunSample);

    file.open("data/sounds/metallic.ogg");
    mMetallicSample.loadSampleData(file);
    mMetallicAudio.setSample(mMetallicSample);

    file.open("data/sounds/squash.ogg");
    mSquashSample.loadSampleData(file);
    mSquashAudio.setSample(mSquashSample);

    file.open("data/sounds/grunt.ogg");
    mGruntSample.loadSampleData(file);
    mGruntAudio.setSample(mGruntSample);

    file.open("data/sounds/pickup.ogg");
    mPickupSample.loadSampleData(file);
    mPickupAudio.setSample(mPickupSample);

    file.open("data/sounds/shovel.ogg");
    mShovelSample.loadSampleData(file);
    mShovelAudio.setSample(mShovelSample);

    mStormStream.openFile("data/sounds/storm.ogg");
    mStormStream.setLooping(true);
    mStormHandle = mAudioPlayer.play(mStormStream);
    mAudioPlayer.setGain(mStormHandle, 0.0f);
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
    std::function<void(const std::string&)> soundPlayer = std::bind(&PlantGuns::playAudio, this, std::placeholders::_1);

    mPlayer.setTexture(mTextures.at("hat"));
    mPlayer.setPosition({550.0f, 450.0f});
    mPlayer.giveWeapon(std::unique_ptr<Weapon>(new Pistol(mTextures, soundPlayer)));
    mPlayer.giveWeapon(std::unique_ptr<Weapon>(new Shotgun(mTextures, soundPlayer)));
    mPlayer.giveSeeds(seedFactory(PISTOL));
    mPlayer.giveSeeds(seedFactory(SHOTGUN));
}

void PlantGuns::setupLevel()
{
    mLevel.setTextures(mTextures);
}

void PlantGuns::update()
{
    std::function<void(const std::string&)> soundPlayer = std::bind(&PlantGuns::playAudio, this, std::placeholders::_1);

    if(!mPlayer.isDead())
    {
        mLevel.update(&mPlayer, soundPlayer);
        mPlayer.update();
    }
    else
        mLevel.update(nullptr, soundPlayer);

    if(mStormGain < mStormGainTarget - 0.001)
    {
        mStormGain += 0.005;
        mAudioPlayer.setGain(mStormHandle, mStormGain);
    }
    else if(mStormGain > mStormGainTarget + 0.001)
    {
        mStormGain -= 0.005;
        mAudioPlayer.setGain(mStormHandle, mStormGain);
    }
}
