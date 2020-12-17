//
// Created by pless on 09/12/2020.
//
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

#include "HomeStartScene.h"
#include "start.h"
#include "HomeMusic.h"
#include "GameScreen.h"
#include "../sprites/cloud/shared.c"
#include "../sprites/cloud/cloud0.c"
#include "../sprites/cloud/cloud1.c"
#include "../sprites/cloud/cloud2.c"

std::vector<Background *> HomeStartScene::backgrounds() {
    return {
            bgStartScreen.get()
    };
}
std::vector<Sprite *> HomeStartScene::sprites(){
    return{
        cloud0.get(),
        cloud1.get(),
        cloud2.get(),
        cloud3.get(),
        cloud4.get()
    };
}


void HomeStartScene::load() {

    timer = 0;

    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1; //Turning off background 2 and 3

    engine.get()->enableText();

    //Create spritebuilder to create sprites
    SpriteBuilder<Sprite> builder;

    cloud0 = builder
            .withData(cloud0Tiles, sizeof(cloud0Tiles))
            .withSize(SIZE_32_32)
            .withLocation((GBA_SCREEN_WIDTH+20), 3)
            .buildPtr();

    cloud1 = builder
            .withData(cloud1Tiles, sizeof(cloud1Tiles))
            .withSize(SIZE_32_32)
            .withLocation(-80, 35)
            .buildPtr();

    cloud2 = builder
            .withData(cloud2Tiles, sizeof(cloud2Tiles))
            .withSize(SIZE_32_32)
            .withLocation((GBA_SCREEN_WIDTH+20), 27)
            .buildPtr();

    cloud3 = builder
            .withData(cloud0Tiles, sizeof(cloud0Tiles))
            .withSize(SIZE_32_32)
            .withLocation(-50, 15)
            .buildPtr();

    cloud4 = builder
            .withData(cloud1Tiles, sizeof(cloud1Tiles))
            .withSize(SIZE_32_32)
            .withLocation((GBA_SCREEN_WIDTH+60), 22)
            .buildPtr();

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(StartPal, sizeof(StartPal)));

    bgStartScreen = std::unique_ptr<Background>(new Background(1, StartTiles, sizeof(StartTiles), StartMap, sizeof(StartMap)));
    bgStartScreen.get()->useMapScreenBlock(7);  //7 IS GOED

    TextStream::instance().setText("PRESS START", 16, 9);

    engine->enqueueMusic(HomescreenMusic,HomescreenMusicBytes);//music
}

void HomeStartScene::tick(u16 keys) {
    timer++;

    if(keys & KEY_START)
    {
        engine->transitionIntoScene(new GameScreen(engine), new FadeOutScene(1));//engine->transitionIntoScene(new FlyingStuffScene(engine), new FadeOutScene(2));
    }
    if(timer > 5){
        if(cloud0->getX() < -32){
            cloud0->moveTo((GBA_SCREEN_WIDTH+20), 20);
        }
        if(cloud1->getX() > (GBA_SCREEN_WIDTH + 32)){
            cloud1->moveTo(-32, 35);
        }
        if(cloud2->getX() < -20){
            cloud2->moveTo((GBA_SCREEN_WIDTH+20), 27);
        }
        if(cloud3->getX() > (GBA_SCREEN_WIDTH + 32)){
            cloud3->moveTo(-32, 27);
        }
        if(cloud4->getX() < -20){
            cloud4->moveTo((GBA_SCREEN_WIDTH+20), 27);
        }
        cloud0->moveTo((cloud0->getX()-1),cloud0->getY());
        cloud1->moveTo((cloud1->getX()+2),cloud1->getY());
        cloud2->moveTo((cloud2->getX()-2),cloud2->getY());
        cloud3->moveTo((cloud3->getX()+1),cloud3->getY());
        cloud4->moveTo((cloud4->getX()-1),cloud4->getY());
        timer = 0;
    }
}