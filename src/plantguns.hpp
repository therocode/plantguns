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
    private:
        void handleInput();
        void render();
        void setupGraphics();
        void setupPlayer();
        void setupLevel();
        fea::InputHandler mInputHandler;
        fea::Renderer2D mRenderer;
        //fea::AudioPlayer audioPlayer;
        fea::Window mWindow;

        Player mPlayer;
        Level mLevel;
        std::unordered_map<std::string, fea::Texture> mTextures;
};
