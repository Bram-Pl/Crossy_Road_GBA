//
// Created by pless on 13/01/2021.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "finishScene.h"

#include "../background/bgFinishScene.c"
#include "HomeStartScene.h"

std::vector<Background *> finishScene::backgrounds() {
    return{
            bgFinishScene.get()
    };
}

std::vector<Sprite *> finishScene::sprites() {
    std::vector<Sprite *> sprites;

    sprites.push_back(bird.get());
    sprites.push_back(flag.get());
    return{sprites};
}

void finishScene::load() {
    ///Disable Background 2 and 3 to prevent gibberish
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1; //Turning off background 2 and 3

    ///Enable text to be presented on the menu
    engine.get()->enableText();

    //foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bgFinishScenePal, sizeof(bgFinishScenePal)));

    bgFinishScene = std::unique_ptr<Background>(new Background(1,bgFinishSceneTiles, sizeof(bgFinishSceneTiles), bgFinishSceneMap, sizeof(bgFinishSceneMap)));
    bgFinishScene->useMapScreenBlock(16);
    bgFinishScene->scroll(0,0);

    TextStream::instance().setText(time.to_string(),8,12);

    TextStream::instance().setText(std::to_string(numberOfCoins),9,9);

    //TextStream::instance().setText(tCal.to_string(), 14, 9);

}

void finishScene::tick(u16 keys) {
    if(keys & KEY_START)
    {
        ///Transition into the new scene
        engine->transitionIntoScene(new HomeStartScene(engine), new FadeOutScene(1));
    }
}