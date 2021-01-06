//
// Created by pless on 06/01/2021.
//

#include "coin.h"

void coin::setPos(int x, int y) {
    x_position = x;
    y_position = y;
}

void coin::tick() {
    sprite->moveTo(x_position,y_position);
}