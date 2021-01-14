//
// Created by pless on 17/12/2020.
//

#include "bird.h"

#define JumpSizeBird 2
#define delayFly 15
#define delayForward 14

/**
 * @brief gets called every tick
 * @param keys
 */
void bird::tick(u16 keys) {
    ///add tick to timer
    timer++;
    ///detect if 'UP' key is pressed, load the move forward sprite and increment the score by one
    if(keys & KEY_UP){
        if(delayForward < timer){
            timer = 0;

            birdForwardMoveSprite->moveTo(xPosition, yPosition);

            birdForwardSprite->moveTo((GBA_SCREEN_WIDTH + 64), (GBA_SCREEN_HEIGHT + 64));
            birdLeftSprite->moveTo((GBA_SCREEN_WIDTH + 64), (GBA_SCREEN_HEIGHT + 64));
            birdLeftMoveSprite->moveTo((GBA_SCREEN_WIDTH + 64), (GBA_SCREEN_HEIGHT + 64));

            lastMoveForward = true;
            lastMoveRight = false;
            lastMoveLeft = false;
            if(virtualYPos < 480){
                virtualYPos = virtualYPos + 32;
            }
            else if(virtualYPos = 480){
                if(yPosition > 31){
                    yPosition = yPosition - 32;
                    birdForwardMoveSprite->moveTo(xPosition, yPosition);
                }
            }
        }
    }
    ///detect if 'LEFT' key is pressed, load the move left sprite
    if(keys & KEY_LEFT){
        timer = 0;

        if(xPosition > 0) {
            xPosition = xPosition - JumpSizeBird;
        }

        birdLeftMoveSprite->flipHorizontally(false);
        birdLeftMoveSprite->moveTo(xPosition ,yPosition);

        birdForwardSprite->moveTo((GBA_SCREEN_WIDTH + 64), (GBA_SCREEN_HEIGHT + 64));
        birdForwardMoveSprite->moveTo((GBA_SCREEN_WIDTH + 64), (GBA_SCREEN_HEIGHT + 64));
        birdLeftSprite->moveTo((GBA_SCREEN_WIDTH + 64), (GBA_SCREEN_HEIGHT + 64));

        lastMoveForward = false;
        lastMoveLeft = true;
        lastMoveRight = false;
    }
    ///detect if 'RIGHT' key is pressed, load the move right sprite
    if(keys & KEY_RIGHT){
        timer = 0;

        if(xPosition < (GBA_SCREEN_WIDTH - 48)) {
            xPosition = xPosition + JumpSizeBird;
        }

        birdLeftMoveSprite->flipHorizontally(true);
        birdLeftMoveSprite->moveTo(xPosition ,yPosition);

        birdForwardSprite->moveTo((GBA_SCREEN_WIDTH + 64), (GBA_SCREEN_HEIGHT + 64));
        birdForwardMoveSprite->moveTo((GBA_SCREEN_WIDTH + 64), (GBA_SCREEN_HEIGHT + 64));
        birdLeftSprite->moveTo((GBA_SCREEN_WIDTH + 64), (GBA_SCREEN_HEIGHT + 64));

        lastMoveForward = false;
        lastMoveLeft = false;
        lastMoveRight = true;
    }
    ///Stop the move forward sprite and replace with last movement forward sprite after 'delayfly' time generates the effect of 'flying' forward
    if(lastMoveForward && timer > delayFly){
        birdForwardSprite->moveTo(xPosition, yPosition);
        birdForwardMoveSprite->moveTo((GBA_SCREEN_WIDTH + 64), (GBA_SCREEN_HEIGHT + 64));
        lastMoveForward = !lastMoveForward;
    }
    ///Stop the move left sprite and replace with last movement left sprite after 'delayfly' time generates the effect of 'flying' left
    if(lastMoveLeft && timer > delayFly){
        birdLeftSprite->flipHorizontally(false);
        birdLeftSprite->moveTo(xPosition, yPosition);
        birdLeftMoveSprite->moveTo((GBA_SCREEN_WIDTH + 64), (GBA_SCREEN_HEIGHT + 64));
        lastMoveLeft = !lastMoveLeft;
    }
    ///Stop the move right sprite and replace with last movement right sprite after 'delayfly' time generates the effect of 'flying' right
    if(lastMoveRight && timer > delayFly){
        birdLeftSprite->flipHorizontally(true);
        birdLeftSprite->moveTo(xPosition, yPosition);
        birdLeftMoveSprite->moveTo((GBA_SCREEN_WIDTH + 64), (GBA_SCREEN_HEIGHT + 64));
        lastMoveRight = !lastMoveRight;
    }
}
