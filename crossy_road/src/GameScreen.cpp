//
// Created by pless on 16/12/2020.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "GameScreen.h"

#include "../sprites/bird/birdForward.c"
#include "../sprites/bird/birdForwardMove.c"
#include "../sprites/bird/birdLeft.c"
#include "../sprites/bird/birdLeftMove.c"
#include "../sprites/bird/birdRight.c"
#include "../sprites/bird/birdRightMove.c"
#include "../sprites/bird/shared.c"

/*
 * Get Sprites when loading the game
 * birdForward
*/
std::vector<Sprite *> GameScreen::sprites() {
    std::vector<Sprite *> sprites;

    sprites.push_back(birdPlayer->getBirdForwardSprite());
    sprites.push_back(birdPlayer->getbirdForwardMoveSprite());
    sprites.push_back(birdPlayer->getbirdLeftSprite());
    sprites.push_back(birdPlayer->getbirdLeftMoveSprite());
    sprites.push_back(birdPlayer->getbirdRightSprite());
    sprites.push_back(birdPlayer->getbirdRightMoveSprite());

    return{sprites};
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

    birdPlayer = std::unique_ptr<bird>(new bird(        builder //Forward Bird
                                                            .withData(birdForwardTiles, sizeof(birdForwardTiles))
                                                            .withSize(SIZE_32_32)
                                                            .withLocation((GBA_SCREEN_WIDTH/2 - 16), (GBA_SCREEN_HEIGHT - 32))
                                                            .buildPtr(),
                                                        builder //Forward Move Bird
                                                            .withData(birdForwardMoveTiles, sizeof(birdForwardMoveTiles))
                                                            .withSize(SIZE_32_32)
                                                            .withLocation(GBA_SCREEN_WIDTH + 32, GBA_SCREEN_HEIGHT + 32)
                                                            .buildPtr(),
                                                        builder //Left Bird
                                                            .withData(birdLeftTiles, sizeof(birdLeftTiles))
                                                            .withSize(SIZE_32_32)
                                                            .withLocation(GBA_SCREEN_WIDTH + 32, GBA_SCREEN_HEIGHT + 32)
                                                            .buildPtr(),
                                                        builder //Left Move Bird
                                                            .withData(birdLeftMoveTiles, sizeof(birdLeftMoveTiles))
                                                            .withSize(SIZE_32_32)
                                                            .withLocation(GBA_SCREEN_WIDTH + 32, GBA_SCREEN_HEIGHT + 32)
                                                            .buildPtr(),
                                                        builder //Right Bird
                                                            .withData(birdRightTiles, sizeof(birdRightTiles))
                                                            .withSize(SIZE_32_32)
                                                            .withLocation(GBA_SCREEN_WIDTH + 32, GBA_SCREEN_HEIGHT + 32)
                                                            .buildPtr(),
                                                        builder //Right Move Bird
                                                            .withData(birdRightMoveTiles, sizeof(birdRightMoveTiles))
                                                            .withSize(SIZE_32_32)
                                                            .withLocation(GBA_SCREEN_WIDTH + 32, GBA_SCREEN_HEIGHT + 32)
                                                            .buildPtr()));
}

    //Game ticks
void GameScreen::tick(u16 keys) {
        TextStream::instance().setText(std::string("Score: ") + std::to_string(birdPlayer->score), 1, 20);

        birdPlayer->tick(keys);
}