//
// Created by pless on 17/12/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BIRD_H
#define GBA_SPRITE_ENGINE_PROJECT_BIRD_H

#include <libgba-sprite-engine/scene.h>
#include "../../crossy_road/sprites/bird/birdForward.c"

class bird {
private:
    std::unique_ptr<Sprite> birdForwardSprite;
    std::unique_ptr<Sprite> birdForwardMoveSprite;
    std::unique_ptr<Sprite> birdLeftSprite;
    std::unique_ptr<Sprite> birdLeftMoveSprite;
    std::unique_ptr<Sprite> birdRightSprite;
    std::unique_ptr<Sprite> birdRightMoveSprite;

    double yPosition;
    bool collision;

    bool movingForward;
    bool movingLeft;
    bool movingRight;

    bool lastMoveForward;
    bool lastMoveLeft;
    bool lastMoveRight;

public:
    double score;
    ///Constructor
    bird(std::unique_ptr<Sprite> birdForwardSprite,
            std::unique_ptr<Sprite> birdForwardMoveSprite,
            std::unique_ptr<Sprite> birdLeftSprite,
            std::unique_ptr<Sprite> birdLeftMoveSprite,
            std::unique_ptr<Sprite> birdRightSprite,
            std::unique_ptr<Sprite> birdRightMoveSprite);

    ///Getters
    Sprite* getBirdForwardSprite() {return birdForwardSprite.get();}
    Sprite* getbirdForwardMoveSprite() {return birdForwardMoveSprite.get();}
    Sprite* getbirdLeftSprite() {return birdLeftSprite.get();}
    Sprite* getbirdLeftMoveSprite() {return birdLeftMoveSprite.get();}
    Sprite* getbirdRightSprite() {return birdRightSprite.get();}
    Sprite* getbirdRightMoveSprite() {return birdRightMoveSprite.get();}

    double getyPosition() {return yPosition;}
    double getScore() {return score;}
    bool isMovingForward() {return movingForward;}
    bool isLastMoveForward() {return lastMoveForward;}
    bool isMovingLeft() {return movingLeft;}
    bool isLastMoveLeft() {return lastMoveLeft;}
    bool isMovingRight() {return movingRight;}
    bool isLastMoveRight() {return lastMoveRight;}

    void tick(u16 keys);
    void move();

};


#endif //GBA_SPRITE_ENGINE_PROJECT_BIRD_H
