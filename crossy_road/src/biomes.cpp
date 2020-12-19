 //
// Created by 11700372 on 19/12/2020.
//

#include "biomes.h"

#define delaySlide 14

///biomes class .cpp file
void biomes::tick(u16 keys) {

     ///add tick to timer
     timer++;

     ///detect if 'UP' key is pressed, slide the first biome and show the second
     if (keys & KEY_UP) {
         if (delaySlide < timer) {
             timer = 0;

             grassSprite->moveTo(xPosition, yPosition);

            grassSprite->moveTo((GBA_SCREEN_WIDTH),(GBA_SCREEN_HEIGHT + 32));
         }
     }

 }