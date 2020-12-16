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
#include "Clouds1.h"
#include "HomeMusic.h"
#include "GameScreen.h"

//HomeStartScene::HomeStartScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine){}

std::vector<Background *> HomeStartScene::backgrounds() {
    return {
            bgStartScreen.get()
    };
}
std::vector<Sprite *> HomeStartScene::sprites(){
    return{};
}


void HomeStartScene::load() {

    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1; //Turning off background 2 and 3

    engine.get()->enableText();

    /*
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(StartPal, sizeof(StartPal)));
    bgStartScreen = std::unique_ptr<Background>(new Background(0, StartTiles, sizeof(StartTiles), StartMap, sizeof(StartMap)));
    bgStartScreen.get()->useMapScreenBlock(24);
 */

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(StartPal, sizeof(StartPal)));

    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(StartPal, sizeof(StartPal)));

    bgStartScreen = std::unique_ptr<Background>(new Background(1, StartTiles, sizeof(StartTiles), StartMap, sizeof(StartMap)));
    bgStartScreen.get()->useMapScreenBlock(7);  //7 IS GOED

    //Clouds_1 = std::unique_ptr<Background>(new Background(2, Clouds1Tiles, sizeof(Clouds1Tiles), Clouds1Map, sizeof(Clouds1Map)));
    //Clouds_1.get()->useMapScreenBlock(95);

    //SpriteBuilder<Sprite> builder;

    TextStream::instance().setText("PRESS START", 16, 9);


/*
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    SpriteBuilder<Sprite> builder;

    TextStream::instance().setText("PRESS START", 3, 8);
*/

    engine->enqueueMusic(HomescreenMusic,HomescreenMusicBytes);//music
}

void HomeStartScene::tick(u16 keys) {
    if(keys & KEY_START)
    {
        engine->transitionIntoScene(new GameScreen(engine), new FadeOutScene(1));//engine->transitionIntoScene(new FlyingStuffScene(engine), new FadeOutScene(2));
    }
}