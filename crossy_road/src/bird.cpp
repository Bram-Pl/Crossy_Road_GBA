//
// Created by pless on 17/12/2020.
//

#include "bird.h"

#define JumpSizeBird 2
#define delayFly 15
#define delayForward 14

void bird::tick(u16 keys) {

    timer++;

    if(keys & KEY_UP){
        if(delayForward < timer){
            timer = 0;

            birdForwardMoveSprite->moveTo(xPosition, yPosition);

            birdForwardSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
            birdLeftSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
            birdLeftMoveSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
            birdRightSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
            birdRightMoveSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));

            lastMoveForward = true;
            lastMoveRight = false;
            lastMoveLeft = false;

            score++;
        }
    }
    if(keys & KEY_LEFT){
        timer = 0;

        if(xPosition > 0) {
            xPosition = xPosition - JumpSizeBird;
        }

        birdLeftMoveSprite->moveTo(xPosition ,yPosition);

        birdForwardSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
        birdForwardMoveSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
        birdLeftSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
        birdRightSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
        birdRightMoveSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));

        lastMoveForward = false;
        lastMoveLeft = true;
        lastMoveRight = false;
    }
    if(keys & KEY_RIGHT){
        timer = 0;

        if(xPosition < (GBA_SCREEN_WIDTH - 48)) {
            xPosition = xPosition + JumpSizeBird;
        }

        birdRightMoveSprite->moveTo(xPosition ,yPosition);

        birdForwardSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
        birdForwardMoveSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
        birdLeftSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
        birdLeftMoveSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
        birdRightSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));

        lastMoveForward = false;
        lastMoveLeft = false;
        lastMoveRight = true;
    }

    if(lastMoveForward && timer > delayFly){
        birdForwardSprite->moveTo(xPosition, yPosition);
        birdForwardMoveSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
        lastMoveForward = !lastMoveForward;
    }

    if(lastMoveLeft && timer > delayFly){
        birdLeftSprite->moveTo(xPosition, yPosition);
        birdLeftMoveSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
        lastMoveLeft = !lastMoveLeft;
    }

    if(lastMoveRight && timer > delayFly){
        birdRightSprite->moveTo(xPosition, yPosition);
        birdRightMoveSprite->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
        lastMoveRight = !lastMoveRight;
    }
}
