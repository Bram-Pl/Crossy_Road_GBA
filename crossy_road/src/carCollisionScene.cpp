//
// Created by pless on 10/01/2021.
//

#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

#include "carCollisionScene.h"
#include "HomeStartScene.h"

#include "../sprites/explosion/explosion.c"
#include "../sprites/explosion/shared.c"
#include "../sprites/explosion/birdLeft.c"
#include "../sprites/explosion/birdLeftMove.c"
#include "../sprites/explosion/Car.c"

#include "../background/bgCarCollision.c"

/**
 * @brief collects backgrounds in vector
 * @return vector of Background type
 */
std::vector<Background *> carCollisionScene::backgrounds() {
    return{
            bgCarCollision.get()
    };
}

/**
 * @brief collects sprites in vector
 * @return vector of Sprite type
 */
std::vector<Sprite *> carCollisionScene::sprites() {
    std::vector<Sprite *> sprites;

    sprites.push_back(birdLeft.get());
    sprites.push_back(car1.get());
    sprites.push_back(explosion.get());
    return{sprites};
}

/**
 * @brief method gets called when scene is loaded in
 */
void carCollisionScene::load() {
    ///Disable Background 2 and 3 to prevent gibberish
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1; //Turning off background 2 and 3

    ///Enable text to be presented on the menu
    engine.get()->enableText();

    ///Palette for the sprites in the foreground and palette for the background
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bgCarCollisionPal, sizeof(bgCarCollisionPal)));
    ///Background parameters
    bgCarCollision = std::unique_ptr<Background>(new Background(1,bgCarCollisionTiles, sizeof(bgCarCollisionTiles), bgCarCollisionMap, sizeof(bgCarCollisionMap)));
    bgCarCollision->useMapScreenBlock(16);
    bgCarCollision->scroll(0,0);

    ///Build sprites using builder
    birdLeft = builder
            .withData(birdLeftMoveTiles, sizeof(birdLeftMoveTiles))
            .withSize(SIZE_32_32)
            .withLocation(208, ((GBA_SCREEN_HEIGHT/2) - 16))
            .buildPtr();

    car1 = builder
            .withData(CarTiles, sizeof(CarTiles))
            .withSize(SIZE_32_32)
            .withLocation(0, ((GBA_SCREEN_HEIGHT/2) - 16))
            .buildPtr();

    explosion = builder
            .withData(explosionTiles, sizeof(explosionTiles))
            .withSize(SIZE_32_32)
            .withAnimated(9,15)
            .withLocation((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32))
            .buildPtr();
    explosion->stopAnimating();

    ///Set text on screen
    TextStream::instance().setText("Game Over!",15,10);
    TextStream::instance().setText("Death by car... Noob",16,6);
}

/**
 * @brief gets called every tick
 * @param keys
 */
void carCollisionScene::tick(u16 keys) {
    timer++;
    if(!birdLeft->collidesWith(*car1.get())){
        int birdX = birdLeft->getX() - 1;
        birdLeft->moveTo(birdX, birdLeft->getY());

        int carX = car1->getX() + 1;
        car1->moveTo(carX, car1->getY());
    }
    else{
        if(!playedSound){engine->enqueueSound(explosionSound, explosionSound_bytes); playedSound = true;}
        birdLeft->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
        car1->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
        explosion->moveTo((GBA_SCREEN_WIDTH / 2) - 16, (GBA_SCREEN_HEIGHT / 2) - 24);
        explosion->animate();
    }
    if(timer > 200){
        explosion->moveTo(GBA_SCREEN_WIDTH+32, GBA_SCREEN_HEIGHT+32);
        explosion->stopAnimating();
    }
    if(keys & KEY_START){engine->transitionIntoScene(new HomeStartScene(engine), new FadeOutScene(1));}
}