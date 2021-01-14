//
// Created by pless on 13/01/2021.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "finishScene.h"
#include "HomeStartScene.h"
#include "../background/bgFinishScene.c"
#include "../music/finish.h"

///Multiplier for coins that get deducted
#define multiplierCoins 1000

/**
 * @brief collects backgrounds in vector
 * @return vector of Background type
 */
std::vector<Background *> finishScene::backgrounds() {
    return{
            bgFinishScene.get()
    };
}

/**
 * @brief method gets called when scene is loaded in
 */
void finishScene::load() {
    ///Start the best finish music ever
    engine->enqueueMusic(finish, finish_bytes);
    ///Disable Background 2 and 3 to prevent gibberish
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1; //Turning off background 2 and 3

    ///Enable text to be presented on the menu
    engine.get()->enableText();

    ///Background parameters
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bgFinishScenePal, sizeof(bgFinishScenePal)));
    bgFinishScene = std::unique_ptr<Background>(new Background(1,bgFinishSceneTiles, sizeof(bgFinishSceneTiles), bgFinishSceneMap, sizeof(bgFinishSceneMap)));
    bgFinishScene->useMapScreenBlock(16);
    bgFinishScene->scroll(0,0);

    #pragma region time calculations
    difTime = std::to_string(1 * numberOfCoins) + " s";
    t_Calms = timems - (multiplierCoins * numberOfCoins);

    int timems_min = timems/(1000*60);
    timems -= timems_min;

    int timems_sec =  timems/1000;
    timems -= timems_sec;

    totalTime = std::to_string(timems_min) + ":" + std::to_string(timems_sec) + ":" + std::to_string(timems / 100);

    int t_Calms_min = t_Calms/(1000*60);
    t_Calms -= t_Calms_min;

    int t_Calms_sec =  t_Calms/1000;
    t_Calms -= t_Calms_sec;

    deltaTime = std::to_string(t_Calms_min) + ":" + std::to_string(t_Calms_sec) + ":" + std::to_string(timems / 100);
    #pragma endregion time calculations

    ///Text displayed on finish menu
    TextStream::instance().setText(totalTime,7,12); //total playtime
    TextStream::instance().setText(std::to_string(numberOfCoins),(19/2),9); //number of coins picked up
    TextStream::instance().setText(difTime,(19/2),12);  //
    TextStream::instance().setText(deltaTime, 13, 12);
}

/**
 * @brief gets called every tick
 * @param keys
 */
void finishScene::tick(u16 keys) {
    if(keys & KEY_START){engine->transitionIntoScene(new HomeStartScene(engine), new FadeOutScene(1));}
}