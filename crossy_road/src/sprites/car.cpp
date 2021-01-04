//
// Created by pless on 04/01/2021.
//

#include "car.h"

void car::setPos(int x, int y) {
    x_position = x;
    y_position = y;
}

void car::tick() {
    sprite->moveTo(x_position,y_position);
    x_position = x_position + 1;
}