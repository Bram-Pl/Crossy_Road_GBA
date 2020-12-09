//
// Created by pless on 09/12/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_HOMESTARTSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_HOMESTARTSCENE_H


#include <libgba-sprite-engine/scene.h>

class HomeStartScene : public Scene {
private:
    std::unique_ptr<Background> bgStartScreen;

public:
    HomeStartScene(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_HOMESTARTSCENE_H
