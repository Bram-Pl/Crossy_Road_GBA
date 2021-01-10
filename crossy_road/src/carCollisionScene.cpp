//
// Created by pless on 10/01/2021.
//

#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "carCollisionScene.h"

#include "../sprites/explosion/explosion.c"
#include "../sprites/explosion/shared.c"
#include "../sprites/explosion/birdLeft.c"
#include "../sprites/explosion/birdLeftMove.c"
#include "../sprites/explosion/Car.c"

std::vector<Background *> carCollisionScene::backgrounds() {
    return{
        //backgrounds
    };
}
std::vector<Sprite *> carCollisionScene::sprites() {
    std::vector<Sprite *> sprites;

    sprites.push_back(birdLeft.get());
    sprites.push_back(car1.get());
    sprites.push_back(explosion.get());
    return{sprites};
}

void carCollisionScene::load() {
    ///Disable Background 2 and 3 to prevent gibberish
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1; //Turning off background 2 and 3

    ///Enable text to be presented on the menu
    engine.get()->enableText();

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));

    birdLeft = builder
            .withData(birdLeftMoveTiles, sizeof(birdLeftMoveTiles))
            .withSize(SIZE_32_32)
            .withLocation(208, (GBA_SCREEN_HEIGHT/2))
            .buildPtr();

    car1 = builder
            .withData(CarTiles, sizeof(CarTiles))
            .withSize(SIZE_32_32)
            .withLocation(0, (GBA_SCREEN_HEIGHT/2))
            .buildPtr();

    explosion = builder
            .withData(explosionTiles, sizeof(explosionTiles))
            .withSize(SIZE_32_32)
            .withAnimated(9,15)
            .withLocation((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32))
            .buildPtr();
    explosion->stopAnimating();

    TextStream::instance().setText("Game Over!",15,10);
    TextStream::instance().setText("Death by car... Noob",16,6);

}

void carCollisionScene::tick(u16 keys) {
    if(!birdLeft->collidesWith(*car1.get())){
        int birdX = birdLeft->getX() - 1;
        birdLeft->moveTo(birdX, birdLeft->getY());

        int carX = car1->getX() + 1;
        car1->moveTo(carX, car1->getY());
    }
    else{
        birdLeft->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
        car1->moveTo((GBA_SCREEN_WIDTH + 32), (GBA_SCREEN_HEIGHT + 32));
        explosion->moveTo((GBA_SCREEN_WIDTH / 2) - 16, (GBA_SCREEN_HEIGHT / 2) - 16);
        explosion->animate();
    }
}