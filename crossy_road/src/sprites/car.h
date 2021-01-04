//
// Created by pless on 04/01/2021.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_CAR_H
#define GBA_SPRITE_ENGINE_PROJECT_CAR_H

#include <libgba-sprite-engine/sprites/sprite.h>

class car {
private:
    std::unique_ptr<Sprite> sprite;

    int x_position;
    int y_position;

public:
    car(std::unique_ptr<Sprite> sprite) : sprite(std::move(sprite)) {}

    void tick();
    bool isOffScreen() {return sprite->isOffScreen(); }
    Sprite* getSprite() {return sprite.get(); }
    void setPos(int x, int y);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_CAR_H
