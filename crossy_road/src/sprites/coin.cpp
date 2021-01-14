//
// Created by pless on 06/01/2021.
//

#include <libgba-sprite-engine/gba_engine.h>
#include "coin.h"

/**
 * @brief change te position of the car
 * @param x position of the coin
 * @param y position of the coin
 */
void coin::setPos(int x, int y) {
    x_position = x;
    y_position = y;
}

/**
 * @brief detect if coin is off the screen
 * @return true if coin is below the y level
 */
bool coin::isOffScreenDown() {
    return(y_position >= GBA_SCREEN_HEIGHT + 32);
}

/**
 * @brief gets called every tick
 */
void coin::tick() {
    sprite->moveTo(x_position,y_position);
}