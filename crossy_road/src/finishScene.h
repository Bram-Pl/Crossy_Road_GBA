//
// Created by pless on 13/01/2021.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_FINISHSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_FINISHSCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <../../engine/include/libgba-sprite-engine/timer.h>
#include <ctime>

class finishScene : public Scene{
private:
    std::unique_ptr<Background> bgFinishScene;
    std::unique_ptr<Sprite> flag;
    std::unique_ptr<Sprite> bird;

    unsigned char numberOfCoins;

    Timer time;

    //SpriteBuilder<Sprite> builder;

public:

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    finishScene(std::shared_ptr<GBAEngine> engine, unsigned char  nCoins, Timer playTime) : Scene(engine) {numberOfCoins = nCoins; time = playTime;}

    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_FINISHSCENE_H
