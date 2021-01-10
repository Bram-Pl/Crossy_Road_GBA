//
// Created by pless on 10/01/2021.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_RIVERCOLLISIONSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_RIVERCOLLISIONSCENE_H


#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>

class riverCollisionScene : public Scene{
private:
    std::unique_ptr<Background> bgRiverCollision;
    std::unique_ptr<Sprite> water;
    std::unique_ptr<Sprite> bird;

    SpriteBuilder<Sprite> builder;

    int timer = 0;

public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    riverCollisionScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_RIVERCOLLISIONSCENE_H
