//
// Created by pless on 10/01/2021.
//

#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "riverCollisionScene.h"

#include "../sprites/waterDrip/birdForwardMove.c"
#include "../sprites/waterDrip/shared.c"
#include "../sprites/waterDrip/waterBubble.c"
#include "../background/bgRiverCollision.c"


std::vector<Background *> riverCollisionScene::backgrounds() {
    return{
            bgRiverCollision.get()
    };
}
std::vector<Sprite *> riverCollisionScene::sprites() {
    std::vector<Sprite *> sprites;

    sprites.push_back(water.get());
    sprites.push_back(bird.get());
    return{sprites};
}

void riverCollisionScene::load() {
    ///Disable Background 2 and 3 to prevent gibberish
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1; //Turning off background 2 and 3

    ///Enable text to be presented on the menu
    engine.get()->enableText();

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bgRiverCollisionPal, sizeof(bgRiverCollisionPal)));

    bgRiverCollision = std::unique_ptr<Background>(new Background(1,bgRiverCollisionTiles, sizeof(bgRiverCollisionTiles), bgRiverCollisionMap, sizeof(bgRiverCollisionMap)));
    bgRiverCollision->useMapScreenBlock(16);
    bgRiverCollision->scroll(0,0);

    bird = builder
            .withData(birdForwardMoveTiles, sizeof(birdForwardMoveTiles))
            .withSize(SIZE_32_32)
            .withLocation(0, (GBA_SCREEN_HEIGHT/2))
            .buildPtr();

    water = builder
            .withData(waterBubbleTiles, sizeof(waterBubbleTiles))
            .withSize(SIZE_32_32)
            .withAnimated(3,15)
            .withLocation((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32))
            .buildPtr();
    water->stopAnimating();

    TextStream::instance().setText("Game Over!",15,10);
    TextStream::instance().setText("Death by river... Noob",16,6);

}

void riverCollisionScene::tick(u16 keys) {
    timer++;

}