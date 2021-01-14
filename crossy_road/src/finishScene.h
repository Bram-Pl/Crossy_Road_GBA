//
// Created by pless on 13/01/2021.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_FINISHSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_FINISHSCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>

class finishScene : public Scene{
private:
    ///Time calculations in milliseconds
    int timems;     //totalTime in milliseconds
    int t_Calms;    //calculated time in milliseconds
    unsigned char numberOfCoins;    //Number of coins picked up in the game

    std::string totalTime;  //string of totaltime MM:ss:ms
    std::string deltaTime;  //string of deltaTime MM:ss:ms
    std::string difTime;    //string of difTime MM:ss:ms

    std::unique_ptr<Background> bgFinishScene; //background for finish scene
public:
    ///Constructor finish scene
    finishScene(std::shared_ptr<GBAEngine> engine, unsigned char  nCoins, int playTime) : Scene(engine) {numberOfCoins = nCoins; timems = playTime;}

    ///Vector with sprites and backgrounds
    std::vector<Sprite *> sprites() {};
    std::vector<Background *> backgrounds() override;

    ///Generic scene methods
    void load() override;
    void tick(u16 keys) override;
};
#endif //GBA_SPRITE_ENGINE_PROJECT_FINISHSCENE_H
