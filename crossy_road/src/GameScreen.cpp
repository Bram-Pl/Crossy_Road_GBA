//
// Created by pless on 16/12/2020.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include "GameScreen.h"
#include "../sprites/bird/birdForward.c"
#include "../sprites/bird/shared.c"

/*
 * Get Sprites when loading the game
 * birdForward
*/
std::vector<Sprite *> GameScreen::sprites() {
    return{
            birdForward.get()
    };
}

/*
 * Get backgrounds when loading the game
 * bgBasic, currently empty
*/
std::vector<Background *> GameScreen::backgrounds() {
    return {
        //bgBasic.get()
    };
}

/*
 * Upon loading the scene:
*/
void GameScreen::load() { //what to do upon loading

    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1; //Only enable to layers needed.

    //TextStream::instance().setText("Test Fase", 16, 9); //Test text

    //Set Foreground/background palette
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));

    //Create spritebuilder to create sprites
    SpriteBuilder<Sprite> builder;

    birdForward = builder
            .withData(birdForwardTiles, sizeof(birdForwardTiles))
            .withSize(SIZE_32_32)
            .withLocation(104, 128) //xmax = 240; ymax = 160
            .buildPtr();

}

    //Game ticks
void GameScreen::tick(u16 keys) {

}