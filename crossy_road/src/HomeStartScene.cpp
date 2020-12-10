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
    //bgStartScreen.get()->useMapScreenBlock(24);

    SpriteBuilder<Sprite> builder;

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

}