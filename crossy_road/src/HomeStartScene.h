//
// Created by pless on 09/12/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_HOMESTARTSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_HOMESTARTSCENE_H

#include <libgba-sprite-engine/scene.h>

class HomeStartScene : public Scene {
private:
    ///Background and sprites used in scene
    std::unique_ptr<Background> bgStartScreen;
    std::unique_ptr<Sprite> cloud0;
    std::unique_ptr<Sprite> cloud1;
    std::unique_ptr<Sprite> cloud2;
    std::unique_ptr<Sprite> cloud3;
    std::unique_ptr<Sprite> cloud4;

    ///timer to move the clouds
    int timer;
public:
    ///Constructor homestart scene
    HomeStartScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    ///Vector with sprites and backgrounds
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    ///Generic scene methods
    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_HOMESTARTSCENE_H
