//
// Created by pless on 10/01/2021.
//

#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

#include "riverCollisionScene.h"

#include "../sprites/waterDrip/birdForwardMove.c"
#include "../sprites/waterDrip/shared.c"
#include "../sprites/waterDrip/waterBubble.c"
#include "../background/bgRiverCollision.c"
#include "HomeStartScene.h"
#include "../soundEffects/dropSound.h"

/**
 * @brief collects backgrounds in vector
 * @return vector of Background type
 */
std::vector<Background *> riverCollisionScene::backgrounds() {
    return{
            bgRiverCollision.get()
    };
}

/**
 * @brief collects sprites in vector
 * @return vector of Sprite type
 */
std::vector<Sprite *> riverCollisionScene::sprites() {
    std::vector<Sprite *> sprites;

    sprites.push_back(water.get());
    sprites.push_back(bird.get());
    return{sprites};
}

/**
 * @brief method gets called when scene is loaded in
 */
void riverCollisionScene::load() {
    ///Disable Background 2 and 3 to prevent gibberish
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1; //Turning off background 2 and 3

    ///Enable text to be presented on the menu
    engine.get()->enableText();

    ///Palette for the sprites in the foreground and palette for the background
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bgRiverCollisionPal, sizeof(bgRiverCollisionPal)));
    ///Background parameters
    bgRiverCollision = std::unique_ptr<Background>(new Background(1,bgRiverCollisionTiles, sizeof(bgRiverCollisionTiles), bgRiverCollisionMap, sizeof(bgRiverCollisionMap)));
    bgRiverCollision->useMapScreenBlock(16);
    bgRiverCollision->scroll(0,0);

    ///Build sprites using builder
    bird = builder
            .withData(birdForwardMoveTiles, sizeof(birdForwardMoveTiles))
            .withSize(SIZE_32_32)
            .withLocation((GBA_SCREEN_WIDTH/2) - 16, (GBA_SCREEN_HEIGHT + 32))
            .buildPtr();

    water = builder
            .withData(waterBubbleTiles, sizeof(waterBubbleTiles))
            .withSize(SIZE_32_32)
            .withAnimated(3,15)
            .withLocation((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32))
            .buildPtr();
    water->stopAnimating();

    ///Set text on screen
    TextStream::instance().setText("Game Over!",15,10);
    TextStream::instance().setText("Death by river... Noob",16,6);
}

/**
 * @brief gets called every tick
 * @param keys
 */
void riverCollisionScene::tick(u16 keys) {
    timer++;
    if(bird->getY() != (GBA_SCREEN_HEIGHT/2)-16){
        int birdY = bird->getY() - 1;
        bird->moveTo(bird->getX(), birdY);
    }
    else{
        if(!playedSound){engine->enqueueSound(dropSound, dropSound_bytes); playedSound = true;}
        bird->moveTo(GBA_SCREEN_WIDTH+32, GBA_SCREEN_HEIGHT+32);
        water->moveTo((GBA_SCREEN_WIDTH/2)-16, ((GBA_SCREEN_HEIGHT/2)-16));
        water->makeAnimated(0,3,5);
    }
    if(timer > 200){
        water->moveTo(GBA_SCREEN_WIDTH+32, GBA_SCREEN_HEIGHT+32);
        water->stopAnimating();
    }

    if(keys & KEY_START){engine->transitionIntoScene(new HomeStartScene(engine), new FadeOutScene(1));}
}