//
// Created by pless on 16/12/2020.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "GameScreen.h"
#include "../music/InGame.h"

///Shared palette
#include "../sprites/sharedPalette.c"

///bird includes
#include "../sprites/bird/birdForward.c"
#include "../sprites/bird/birdForwardMove.c"
#include "../sprites/bird/birdLeft.c"
#include "../sprites/bird/birdLeftMove.c"

///Load sprites into vector
std::vector<Sprite *> GameScreen::sprites() {
    std::vector<Sprite *> sprites;

    sprites.push_back(birdPlayer->getBirdForwardSprite());
    sprites.push_back(birdPlayer->getbirdForwardMoveSprite());
    sprites.push_back(birdPlayer->getbirdLeftSprite());
    sprites.push_back(birdPlayer->getbirdLeftMoveSprite());

    return{sprites};
}

///Get background in game, may be removed if backgrounds are sprite ***
std::vector<Background *> GameScreen::backgrounds() {
    return {
        //bgBasic.get()
    };
}

///When loading the scene this happens
void GameScreen::load() {

    ///Disable Background 2 and 3 to prevent gibberish
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1;

    ///Set colour palette for foreground(sprites) and background
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPalettePal, sizeof(sharedPalettePal)));

    ///Add birdPlayer to the game and call the possible sprites, only birdForward is visible in the screen
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
                                                            .buildPtr()));

    engine->enqueueMusic(InGame, InGame_bytes);
}

///Every tick in game
void GameScreen::tick(u16 keys) {
    ///Display the current score
    TextStream::instance().setText(std::string("Score:") + std::to_string(birdPlayer->score), 1, 19);

    ///Run the tick() function of birdPlayer
    birdPlayer->tick(keys);
}