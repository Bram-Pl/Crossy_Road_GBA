//
// Created by pless on 16/12/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GAMESCREEN_H
#define GBA_SPRITE_ENGINE_PROJECT_GAMESCREEN_H


#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "sprites/bird.h"
#include "sprites/car.h"

class GameScreen : public Scene {
private:
    ///Declaration of background and sprites
    std::unique_ptr<Background> bgBasic;
    std::unique_ptr<bird> birdPlayer;

    ///Create spritebuilder to create sprites
    SpriteBuilder<Sprite> builder;

    ///Car
    std::unique_ptr<Sprite> someCarSprite;
    std::vector<std::unique_ptr<car>> cars;
    std::unique_ptr<car> createCar();
    void removeCarsOffScreen();

    bool generateOne = false;

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
