//
// Created by pless on 09/12/2020.
//
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

#include "HomeStartScene.h"
#include "../background/startscreen.c"
#include "GameScreen.h"
#include "../sprites/cloud/shared.c"
#include "../sprites/cloud/cloud0.c"
#include "../sprites/cloud/cloud1.c"
#include "../sprites/cloud/cloud2.c"
#include "../music/CrossyRoadSoundTrack.h"
#define cloudTick 5

/**
 * @brief collects backgrounds in vector
 * @return vector of Background type
 */
std::vector<Background *> HomeStartScene::backgrounds() {
    return {
            bgStartScreen.get()
    };
}

/**
 * @brief collects sprites in vector
 * @return vector of Sprite type
 */
std::vector<Sprite *> HomeStartScene::sprites(){
    return{
        cloud0.get(),
        cloud1.get(),
        cloud2.get(),
        cloud3.get(),
        cloud4.get()
    };
}

/**
 * @brief method gets called when scene is loaded in
 */
void HomeStartScene::load() {
    ///Default timer to value zero for the movement of clouds
    timer = 0;
    ///Disable Background 2 and 3 to prevent gibberish
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1; //Turning off background 2 and 3

    ///Enable text to be presented on the menu
    engine.get()->enableText();

    ///Create spritebuilder to create sprites
    SpriteBuilder<Sprite> builder;

    #pragma region clouds
    ///Create four cloud sprites
    cloud0 = builder
            .withData(cloud0Tiles, sizeof(cloud0Tiles))
            .withSize(SIZE_32_32)
            .withLocation((GBA_SCREEN_WIDTH+20), 3)
            .buildPtr();

    cloud1 = builder
            .withData(cloud1Tiles, sizeof(cloud1Tiles))
            .withSize(SIZE_32_32)
            .withLocation(-80, 15)
            .buildPtr();

    cloud2 = builder
            .withData(cloud2Tiles, sizeof(cloud2Tiles))
            .withSize(SIZE_32_32)
            .withLocation((GBA_SCREEN_WIDTH+20), 35)
            .buildPtr();

    cloud3 = builder
            .withData(cloud0Tiles, sizeof(cloud0Tiles))
            .withSize(SIZE_32_32)
            .withLocation(-50, 27)
            .buildPtr();

    cloud4 = builder
            .withData(cloud1Tiles, sizeof(cloud1Tiles))
            .withSize(SIZE_32_32)
            .withLocation((GBA_SCREEN_WIDTH+60), 22)
            .buildPtr();
    #pragma endregion cloud

    ///Set colour palette for foreground(sprites) and background
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(StartPal, sizeof(StartPal)));

    ///Background parameters
    bgStartScreen = std::unique_ptr<Background>(new Background(1, StartTiles, sizeof(StartTiles), StartMap, sizeof(StartMap)));
    bgStartScreen.get()->useMapScreenBlock(7);  //7 IS GOED

    ///Add text to the main screen
    TextStream::instance().setText("PRESS START", 16, 9);

    ///Play music
    engine->getTimer()->start();
    engine->enqueueMusic(CrossyRoadSoundTrack, CrossyRoadSoundTrack_bytes);
}

/**
 * @brief gets called every tick
 * @param keys
 */
void HomeStartScene::tick(u16 keys) {
    timer++;

    ///Flip two clouds around it's horizontal line to make them look more unique
    cloud0->flipHorizontally(true);
    cloud4->flipHorizontally(true);

    ///If the "Start" key is pressed, the game will start
    if(keys & KEY_START)
    {
        ///Transition into the new scene
        engine->transitionIntoScene(new GameScreen(engine), new FadeOutScene(1));//engine->transitionIntoScene(new FlyingStuffScene(engine), new FadeOutScene(2));
    }

    ///Move the cloud an 'x' amount of pixels per 5 game ticks
    if(timer > cloudTick){
        ///Check for out of bounds and move the clouds back to start the cycle over
        if(cloud0->getX() < -32){
            cloud0->moveTo((GBA_SCREEN_WIDTH+20), cloud0->getY());
        }
        if(cloud1->getX() > (GBA_SCREEN_WIDTH + 32)){
            cloud1->moveTo(-32, cloud1->getY());
        }
        if(cloud2->getX() < -20){
            cloud2->moveTo((GBA_SCREEN_WIDTH+20), cloud2->getY());
        }
        if(cloud3->getX() > (GBA_SCREEN_WIDTH + 32)){
            cloud3->moveTo(-32, cloud3->getY());
        }
        if(cloud4->getX() < -20){
            cloud4->moveTo((GBA_SCREEN_WIDTH+20), cloud4->getY());
        }
        ///Move the clouds an 'x' amount to it's respective x
        cloud0->moveTo((cloud0->getX()-1),cloud0->getY());
        cloud1->moveTo((cloud1->getX()+2),cloud1->getY());
        cloud2->moveTo((cloud2->getX()-2),cloud2->getY());
        cloud3->moveTo((cloud3->getX()+1),cloud3->getY());
        cloud4->moveTo((cloud4->getX()-1),cloud4->getY());
        ///Reset timer for the cloud tick
        timer = 0;
    }
}