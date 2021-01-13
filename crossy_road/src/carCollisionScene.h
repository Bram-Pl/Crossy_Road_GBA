//
// Created by pless on 10/01/2021.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_CARCOLLISIONSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_CARCOLLISIONSCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>

class carCollisionScene : public Scene{
private:
    std::unique_ptr<Background> bgCarCollision;
    std::unique_ptr<Sprite> explosion;
    std::unique_ptr<Sprite> car1;
    std::unique_ptr<Sprite> birdLeft;

    SpriteBuilder<Sprite> builder;

public:

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    carCollisionScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_CARCOLLISIONSCENE_H
