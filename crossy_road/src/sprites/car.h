//
// Created by pless on 04/01/2021.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_CAR_H
#define GBA_SPRITE_ENGINE_PROJECT_CAR_H

#include <libgba-sprite-engine/sprites/sprite.h>

class car {
private:
    ///Declaration of sprites
    std::unique_ptr<Sprite> sprite;
public:
    ///Constructor car
    car(std::unique_ptr<Sprite> sprite) : sprite(std::move(sprite)) {}
    ///Parameters car
    int x_position;
    int y_position;
    bool switchDir = false;
    bool stdMirror = false;
    ///Methods regarding car
    void tick();
    bool isOffScreenDown() {return sprite->isOffScreenDown(); }
    Sprite* getSprite() {return sprite.get(); }
    void setPos(int x, int y);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_CAR_H
