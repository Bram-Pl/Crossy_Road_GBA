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
    if(!switchDir){
        x_position = x_position - 1;
        if(stdMirror){
            sprite->flipHorizontally(true);
            stdMirror = false;
        }
    }else if(switchDir){
        x_position = x_position + 1;
    }
}