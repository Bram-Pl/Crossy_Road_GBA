//
// Created by pless on 16/12/2020.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <algorithm>

#include "GameScreen.h"
#include "../music/InGame.h"

///Shared palette
#include "../sprites/sharedPalette.c"
#include "../sprites/car/Car.c"

///bird includes
#include "../sprites/bird/birdForward.c"
#include "../sprites/bird/birdForwardMove.c"
#include "../sprites/bird/birdLeft.c"
#include "../sprites/bird/birdLeftMove.c"

///Load sprites into vector
std::vector<Sprite *> GameScreen::sprites() {
    std::vector<Sprite *> sprites;

    sprites.push_back(birdPlayer->getBirdForwardSprite());
    sprites.push_back(birdPlayer->getbirdForwardMoveSprite());
    sprites.push_back(birdPlayer->getbirdLeftSprite());
    sprites.push_back(birdPlayer->getbirdLeftMoveSprite());

    for(auto& c : cars){
        sprites.push_back(c->getSprite());
    }

    sprites.push_back(someCarSprite.get());

    return sprites;
}

///Get background in game, may be removed if backgrounds are sprite ***
std::vector<Background *> GameScreen::backgrounds() {
    return {
        //bgBasic.get()
    };
}

void GameScreen::removeCarsOffScreen() {
    cars.erase(
            std::remove_if(cars.begin(), cars.end(), [](std::unique_ptr<car> &s) {return s->isOffScreen(); }),
            cars.end());
}

std::unique_ptr<car> GameScreen::createCar(){
    return std::unique_ptr<car>(new car(builder
    .withLocation((30),(30))
    .buildWithDataOf(*someCarSprite.get())));
}

///When loading the scene this happens
void GameScreen::load() {

    ///Disable Background 2 and 3 to prevent gibberish
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1;

    ///Set colour palette for foreground(sprites) and background
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));

    ///Add birdPlayer to the game and call the possible sprites, only birdForward is visible in the screen
    birdPlayer = std::unique_ptr<bird>(new bird(        builder //Forward Bird
                                                            .withData(birdForwardTiles, sizeof(birdForwardTiles))
                                                            .withSize(SIZE_32_32)
                                                            .withLocation((GBA_SCREEN_WIDTH/2 - 16), (GBA_SCREEN_HEIGHT - 32))
                                                            .buildPtr(),
                                                        builder //Forward Move Bird
                                                            .withData(birdForwardMoveTiles, sizeof(birdForwardMoveTiles))
                                                            .withSize(SIZE_32_32)
                                                            .withLocation(GBA_SCREEN_WIDTH + 32, GBA_SCREEN_HEIGHT + 32)
                                                            .buildPtr(),
                                                        builder //Left Bird
                                                            .withData(birdLeftTiles, sizeof(birdLeftTiles))
                                                            .withSize(SIZE_32_32)
                                                            .withLocation(GBA_SCREEN_WIDTH + 32, GBA_SCREEN_HEIGHT + 32)
                                                            .buildPtr(),
                                                        builder //Left Move Bird
                                                            .withData(birdLeftMoveTiles, sizeof(birdLeftMoveTiles))
                                                            .withSize(SIZE_32_32)
                                                            .withLocation(GBA_SCREEN_WIDTH + 32, GBA_SCREEN_HEIGHT + 32)
                                                            .buildPtr()));

    someCarSprite = builder
            .withData(CarTiles, sizeof(CarTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH + 32, GBA_SCREEN_HEIGHT + 32)
            .buildPtr();


    engine->enqueueMusic(InGame, InGame_bytes);
}

///Every tick in game
void GameScreen::tick(u16 keys) {

    ///Display the current score
    TextStream::instance().setText(std::string("Score:") + std::to_string(birdPlayer->score), 1, 19);

    ///Run the tick() method of birdPlayer and cars
    birdPlayer->tick(keys);

    for(auto &c : cars) {
        c->tick();

        if(globalYPos != birdPlayer->virtualYPos){

            c->y_position = c->y_position + 32;
        }
    }
    globalYPos = birdPlayer->virtualYPos;

    if(!generateOne){
        cars.push_back(createCar());
        auto &c = cars.at(cars.size() - 1);
        c->setPos(-32,(GBA_SCREEN_HEIGHT - 128));
        cars.push_back(createCar());
        auto &d = cars.at(cars.size() - 1);
        d->setPos(-86,(GBA_SCREEN_HEIGHT - 128));
        cars.push_back(createCar());
        auto &e = cars.at(cars.size() - 1);
        e->setPos(-350,(GBA_SCREEN_HEIGHT - 128));
        generateOne = true;
        engine.get()->updateSpritesInScene();
    }

    checkCollision();
    if(collision){
        ///END THE GAME AND GO TO END SCREEN WITH SCORE
    }
}

void GameScreen::checkCollision(){
    for(auto &c : cars) {
        if(birdPlayer->getBirdForwardSprite()->collidesWith(*c->getSprite()) ||
           birdPlayer->getbirdForwardMoveSprite()->collidesWith(*c->getSprite()) ||
           birdPlayer->getbirdLeftSprite()->collidesWith(*c->getSprite()) ||
           birdPlayer->getbirdLeftMoveSprite()->collidesWith(*c->getSprite())){

            birdPlayer->score = 69;
            collision = true;
        }
    }
}