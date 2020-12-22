//
// Created by pless on 16/12/2020.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "GameScreen.h"

///bird includes
#include "../sprites/bird/birdForward.c"
#include "../sprites/bird/birdForwardMove.c"
#include "../sprites/bird/birdLeft.c"
#include "../sprites/bird/birdLeftMove.c"
#include "../sprites/bird/birdRight.c"
#include "../sprites/bird/birdRightMove.c"
#include "../sprites/shared.c"

///biomes includes
#include "../biomes/Grass/grass.cpp"
#include "../biomes/Grass/grassSlide.cpp"
#include "../biomes/Grass/tree.cpp"
#include "../biomes/Road/road.cpp"
#include "../biomes/Road/car.cpp"
#include "../biomes/Water/water.cpp"
#include "../biomes/Water/treetrunk.cpp"
#include "../biomes/Water/waterlily.cpp"
#include "biomes.h"

///Load sprites into vector
std::vector<Sprite *> GameScreen::sprites() {
    std::vector<Sprite *> sprites;

    //sprites.push_back(biomesSlider->getGrassSprite());

    sprites.push_back(birdPlayer->getBirdForwardSprite());
    sprites.push_back(birdPlayer->getbirdForwardMoveSprite());
    sprites.push_back(birdPlayer->getbirdLeftSprite());
    sprites.push_back(birdPlayer->getbirdLeftMoveSprite());
    sprites.push_back(birdPlayer->getbirdRightSprite());
    sprites.push_back(birdPlayer->getbirdRightMoveSprite());
    grass.get();
    //sprites.push_back(biomesSlider->getGrassSprite());
    //sprites.push_back(biomesSlider->getGrassSprite());
    //sprites.push_back(biomesSlider->getGrassSlideSprite());
    //sprites.push_back(biomesSlider->getRoadSprite());
    //sprites.push_back(biomesSlider->getWaterSprite());

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
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));

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


 /*   biomesSlider = std::unique_ptr<biomes>(new biomes(                  builder //Grass
                                                            .withData(GrassSlideTiles, sizeof(GrassSlideTiles))
                                                            .withSize(SIZE_240_32)
                                                            .withLocation((GBA_SCREEN_WIDTH + 32), GBA_SCREEN_HEIGHT + (1*32))
                                                            .buildPtr()//,

                                                                        builder //Grass Slide
                                                              .withData(GrassSlideTiles, sizeof(GrassSlideTiles))
                                                              .withSize(SIZE_32_32)
                                                              .withLocation((GBA_SCREEN_WIDTH/2 - 16), (GBA_SCREEN_HEIGHT - 32))
                                                              .buildPtr()

                                                              ));
                                                            builder
                                                                  .withData(RoadTiles, sizeof(RoadTiles))
                                                                  .withSize(SIZE_240_32)
                                                                  .withLocation(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT + (2*32))
                                                                  .build(),
                                                          builder
                                                                  .withData(WaterTiles, sizeof(WaterTiles))
                                                                  .withSize(SIZE_240_32)
                                                                  .withLocation(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT + (2*32))
                                                                  .build()));

    ));

 */                                                      grass = builder
                                                                .withData(GrassTiles, sizeof(GrassTiles))
                                                                .withSize(SIZE_240_32)
                                                                .withLocation((5), (3))
                                                                .buildPtr();



}

///Every tick in game
void GameScreen::tick(u16 keys) {
    ///Display the current score
    TextStream::instance().setText(std::string("Score:") + std::to_string(birdPlayer->score), 1, 19);

    ///Run the tick() function of birdPlayer
    birdPlayer->tick(keys);
}