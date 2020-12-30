//
// Created by pless on 16/12/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GAMESCREEN_H
#define GBA_SPRITE_ENGINE_PROJECT_GAMESCREEN_H


#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "bird.h"
#include "biomes.h"

class GameScreen : public Scene {
private:
    ///Declaration of background and sprites
    std::unique_ptr<Background> bgBasic;
    std::unique_ptr<bird> birdPlayer;
    std::unique_ptr<biomes> biomesSlider;

    ///PROOF OF CONCEPT
    std::unique_ptr<Sprite> Grass_0_0;
    std::unique_ptr<Sprite> Grass_0_1;
    std::unique_ptr<Sprite> Grass_0_2;
    std::unique_ptr<Sprite> Grass_0_3;

    ///Create spritebuilder to create sprites
    SpriteBuilder<Sprite> builder;

public:
    ///Constructor
    GameScreen(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    ///Getters
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    ///Other
    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_GAMESCREEN_H
