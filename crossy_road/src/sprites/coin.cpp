//
// Created by pless on 06/01/2021.
//

#include <libgba-sprite-engine/gba_engine.h>
#include "coin.h"

void coin::setPos(int x, int y) {
    x_position = x;
    y_position = y;
}

bool coin::isOffScreenDown() {
    if(y_position >= GBA_SCREEN_HEIGHT + 32){
        return true;
    }
    return false;
}

void coin::tick() {
    sprite->moveTo(x_position,y_position);
}