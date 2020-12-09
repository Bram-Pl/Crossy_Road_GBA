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

HomeStartScene::HomeStartScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine){}

std::vector<Background *> HomeStartScene::backgrounds() {
    return {
            bgStartScreen.get()
    };
}

std::vector<Sprite *> HomeStartScene::sprites(){
    return{};
}

void HomeStartScene::load() {
    engine.get()->enableText();

    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(StartPal, sizeof(StartPal)));
    bgStartScreen = std::unique_ptr<Background>(new Background(0, StartTiles, sizeof(StartTiles), StartMap, sizeof(StartMap)));
    bgStartScreen.get()->useMapScreenBlock(24);
}

void HomeStartScene::tick(u16 keys) {

}