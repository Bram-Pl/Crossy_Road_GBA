//
// Created by pless on 06/01/2021.
//

#include "treeTrunk.h"

/**
 * @brief set position of the treetrunk
 * @param x position of treetrunk
 * @param y position of treetrunk
 */
void treeTrunk::setPos(int x, int y) {
    x_position = x;
    y_position = y;
}

/**
 * @brief called every tick
 */
void treeTrunk::tick() {
    sprite->moveTo(x_position,y_position);
    if(switchDir){
        x_position = x_position + 1;
    }
    else if(!switchDir){
        x_position = x_position - 1;
    }
}