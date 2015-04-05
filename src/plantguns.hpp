#include <fea/audio.hpp>
#include <fea/structure.hpp>
#include <fea/render2d.hpp>
#include <fea/userinterface.hpp>
#include <fea/ui/sdl2windowbackend.hpp>
#include <fea/ui/sdl2inputbackend.hpp>
#include "player.hpp"
#include "level.hpp"

class PlantGuns : public fea::Application
{
    public:
        PlantGuns();
    protected:
        virtual void setup(const std::vector<std::string>& args) override;
        virtual void destroy() override; 
        virtual void loop() override;

        void playAudio(const std::string& name);
    private:
        void handleInput();
        void render();
        void setupAudio();
        void setupGraphics();
        void setupPlayer();
        void setupLevel();
        void update();
        fea::InputHandler mInputHandler;
        fea::Renderer2D mRenderer;
        fea::Window mWindow;

        Player mPlayer;
        Level mLevel;
        std::unordered_map<std::string, fea::Texture> mTextures;

        fea::AudioPlayer mAudioPlayer;
        fea::AudioSample mPistolSample;
        fea::Audio mPistolAudio;
        fea::AudioSample mShotgunSample;
        fea::Audio mShotgunAudio;
        fea::AudioSample mMetallicSample;
        fea::Audio mMetallicAudio;
        fea::AudioSample mSquashSample;
        fea::Audio mSquashAudio;
        fea::AudioSample mGruntSample;
        fea::Audio mGruntAudio;
        fea::AudioSample mPickupSample;
        fea::Audio mPickupAudio;
        fea::AudioSample mShovelSample;
        fea::Audio mShovelAudio;

        fea::AudioFileStream mStormStream;
        fea::AudioHandle mStormHandle;
        float mStormGainTarget;
        float mStormGain;
};
