//
// Created by pless on 06/01/2021.
//

#include "treeTrunk.h"

void treeTrunk::setPos(int x, int y) {
    x_position = x;
    y_position = y;
}

void treeTrunk::tick() {
    sprite->moveTo(x_position,y_position);
    if(switchDir){
        x_position = x_position + 1;
    }
    else if(!switchDir){
        x_position = x_position - 1;
    }
}