//
// Created by pless on 06/01/2021.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_COIN_H
#define GBA_SPRITE_ENGINE_PROJECT_COIN_H

#include <libgba-sprite-engine/sprites/sprite.h>

class coin {
private:
    ///Declaration of sprites
    std::unique_ptr<Sprite> sprite;

public:
    ///Constructor coin
    coin(std::unique_ptr<Sprite> sprite) : sprite(std::move(sprite)) {}
    ///Parameters coin
    int x_position;
    int y_position;
    ///Methods regarding coin
    void tick();
    bool isOffScreenDown();
    Sprite* getSprite() {return sprite.get(); }
    void setPos(int x, int y);
};

#endif //GBA_SPRITE_ENGINE_PROJECT_COIN_H
