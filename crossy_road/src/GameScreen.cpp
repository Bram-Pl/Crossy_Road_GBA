//
// Created by pless on 16/12/2020.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <algorithm>
#include <iostream>

#include "GameScreen.h"
#include "../music/InGame.h"

///Sprites Includes
#include "../sprites/shared.c"
#include "../sprites/bird/birdForward.c"
#include "../sprites/bird/birdForwardMove.c"
#include "../sprites/bird/birdLeft.c"
#include "../sprites/bird/birdLeftMove.c"
#include "../sprites/car/Car.c"
#include "../sprites/treetrunk/TreeTrunk.c"
#include "../sprites/coin/coin.c"

///Load sprites into vector
std::vector<Sprite *> GameScreen::sprites() {
    std::vector<Sprite *> sprites;

    ///BIRDPLAYER: get sprites for all the birds and add to vector
    sprites.push_back(birdPlayer->getBirdForwardSprite());
    sprites.push_back(birdPlayer->getbirdForwardMoveSprite());
    sprites.push_back(birdPlayer->getbirdLeftSprite());
    sprites.push_back(birdPlayer->getbirdLeftMoveSprite());

    ///CARS: get sprites for all the cars and add to vector
    for(auto& c : cars){
        sprites.push_back(c->getSprite());
    }

    ///treeTrunk: get sprites for all the treetrunks and add to vector
    for(auto& t : treeTrunks){
        sprites.push_back((t->getSprite()));
    }

    ///coin: get sprites for all the coins and add to vector
    for(auto& c : coins){
        sprites.push_back((c->getSprite()));
    }

    sprites.push_back(someCarSprite.get());
    sprites.push_back(someTreeTrunkSprite.get());
    sprites.push_back(someCoinSprite.get());

    return sprites;
}

///Get background in game, may be removed if backgrounds are sprite ***
std::vector<Background *> GameScreen::backgrounds() {
    return {
        //bgBasic.get()
    };
}

#pragma region Car Methods
///CARS: Method to remove cars if they are off screen
void GameScreen::removeCarsOffScreenDown(){
    int sizeOfCars = cars.size();

    cars.erase(
            std::remove_if(cars.begin(), cars.end(), [](std::unique_ptr<car> &c) { return c->isOffScreenDown(); }),
            cars.end());

    if(sizeOfCars > cars.size()){
        engine.get()->updateSpritesInScene();
        ReflipSprite();
    }
}

///CARS: Call method to create a single car
std::unique_ptr<car> GameScreen::createCar(){
    return std::unique_ptr<car>(new car(builder
    .buildWithDataOf(*someCarSprite.get())));
}
#pragma endregion Cars

#pragma region TreeTrunks Methods
///CARS: Method to remove cars if they are off screen
void GameScreen::removeTreeTrunksOffScreenDown() {
    int sizeOfTreeTrunks = treeTrunks.size();

    treeTrunks.erase(
            std::remove_if(treeTrunks.begin(), treeTrunks.end(), [](std::unique_ptr<treeTrunk> &t) { return t->isOffScreenDown(); }),
            treeTrunks.end());

    if(sizeOfTreeTrunks > treeTrunks.size()){
        engine.get()->updateSpritesInScene();
        ReflipSprite();
    }
    //engine.get()->updateSpritesInScene(); WHEN Executed EVERY time, we get moon walking chicken...
}

///CARS: Call method to create a single treeTrunk
std::unique_ptr<treeTrunk> GameScreen::createTreeTrunk(){
    return std::unique_ptr<treeTrunk>(new treeTrunk(builder
        .buildWithDataOf(*someTreeTrunkSprite.get())));
}
#pragma endregion TreeTrunks

#pragma region Coins Methods
///CARS: Method to remove cars if they are off screen
void GameScreen::removeCoinsOffScreenDown() {
    int sizeOfCoins = coins.size();

    coins.erase(
            std::remove_if(coins.begin(), coins.end(), [](std::unique_ptr<coin> &c) { return c->isOffScreenDown(); }),
            coins.end());

    if(sizeOfCoins > coins.size()) {
        ReflipSprite();
    }
}

///COINS: Call method to create a single coin
std::unique_ptr<coin> GameScreen::createCoin() {
    return std::unique_ptr<coin>(new coin(builder
        .buildWithDataOf(*someCoinSprite.get())));
}
#pragma endregion Coins

void GameScreen::ReflipSprite() {
    for(auto &c : cars) {
        if(c->switchDir != true){
            c->stdMirror = true;
        }
    }
    engine->updateSpritesInScene();
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

    ///CARS: add template for car, is used to ".buildWithDataOf()"
    someCarSprite = builder
            .withData(CarTiles, sizeof(CarTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH + 32, GBA_SCREEN_HEIGHT + 32)
            .buildPtr();

    ///TREETRUNK: add template for treeTrunk, is used to ".buildWithDataOf()"
    someTreeTrunkSprite = builder
            .withData(TreeTrunkTiles, sizeof(TreeTrunkTiles))
            .withSize(SIZE_32_16)
            .withLocation(GBA_SCREEN_WIDTH + 32, GBA_SCREEN_HEIGHT + 32)
            .buildPtr();

    ///COIN: add template for coin, is used to ".buildWithDataOf()"
    someCoinSprite = builder
            .withData(CoinTiles, sizeof(CoinTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH + 32, GBA_SCREEN_HEIGHT + 32)
            .buildPtr();


    ///Enqueue music to start playing
    engine->enqueueMusic(InGame, InGame_bytes);
}

///Every tick in game
void GameScreen::tick(u16 keys) {

    ///Display the current score
    TextStream::instance().setText(std::string("Score:") + std::to_string(birdPlayer->score), 1, 19);

    ///Run the tick() method of birdPlayer and cars
    birdPlayer->tick(keys);

#pragma region movement sprites

    ///CARS: Check all cars and move their respective Y position according the birds movement
    for(auto &c : cars) {
        c->tick();

        if(globalYPos != birdPlayer->virtualYPos){
            c->y_position = c->y_position + 32;
        }
    }
    ///TREETRUNKS: Check all treetrunks and move their respective Y position according the birds movement
    for(auto &t : treeTrunks) {
        t->tick();

        if(globalYPos != birdPlayer->virtualYPos){
            t->y_position = t->y_position + 32;
        }
    }

    ///COINS: Check all coins and move their respective Y position according the birds movement
    for(auto &c : coins) {
        c->tick();

        if(globalYPos != birdPlayer->virtualYPos){
            c->y_position = c->y_position + 32;
        }
    }

    globalYPos = birdPlayer->virtualYPos;

#pragma endregion movement sprites

    ///GENERATE SPRITES FOR MAP: First call to generate all sprites
    if(!generateOne){
        ///In order of appearence
        //2nd row
        coins.push_back(createCoin());
        auto &co1 = coins.at(coins.size()-1);
        co1->setPos(30, 96);

        //3th row
        cars.push_back(createCar());
        auto &c1 = cars.at(cars.size() - 1);
        c1->switchDir = true;
        c1->setPos(-32,(GBA_SCREEN_HEIGHT - 96));
        cars.push_back(createCar());
        auto &c2 = cars.at(cars.size() - 1);
        c2->switchDir = true;
        c2->setPos(-86,(GBA_SCREEN_HEIGHT - 96));
        cars.push_back(createCar());
        auto &c3 = cars.at(cars.size() - 1);
        c3->switchDir = true;
        c3->setPos(-350,(GBA_SCREEN_HEIGHT - 96));

        //5th row
        treeTrunks.push_back(createTreeTrunk());
        auto &t1 = treeTrunks.at(treeTrunks.size()-1);
        t1->setPos(GBA_SCREEN_WIDTH, 8);
        treeTrunks.push_back(createTreeTrunk());
        auto &t2 = treeTrunks.at(treeTrunks.size()-1);
        t2->setPos(GBA_SCREEN_WIDTH + 86, 8);
        treeTrunks.push_back(createTreeTrunk());
        auto &t3 = treeTrunks.at(treeTrunks.size()-1);
        t3->setPos(GBA_SCREEN_WIDTH + 220, 8);

        //6th row
        coins.push_back(createCoin());
        auto &co2 = coins.at(coins.size()-1);
        co2->setPos(180, -32);

        //7th row
        cars.push_back(createCar());
        auto &c4 = cars.at(cars.size() - 1);
        c4->stdMirror = true;
        c4->setPos(-32,-64);
        cars.push_back(createCar());
        auto &c5 = cars.at(cars.size() - 1);
        c5->stdMirror = true;
        c5->setPos(-86,-64);
        cars.push_back(createCar());
        auto &c6 = cars.at(cars.size() - 1);
        c6->stdMirror = true;
        c6->setPos(-350,-64);

        //8th row
        treeTrunks.push_back(createTreeTrunk());
        auto &t4 = treeTrunks.at(treeTrunks.size()-1);
        t4->setPos(GBA_SCREEN_WIDTH + 32, -88);
        treeTrunks.push_back(createTreeTrunk());
        auto &t5 = treeTrunks.at(treeTrunks.size()-1);
        t5->setPos(GBA_SCREEN_WIDTH + 120, -88);
        treeTrunks.push_back(createTreeTrunk());
        auto &t6 = treeTrunks.at(treeTrunks.size()-1);
        t6->setPos(GBA_SCREEN_WIDTH + 260, -88);

        /*//9th row
        coins.push_back(createCoin());
        auto &co3 = coins.at(coins.size()-1);
        co3->setPos(180, -128);*/

        /*//10th row
        coins.push_back(createCoin());
        auto &co4 = coins.at(coins.size()-1);
        co4->setPos(10, -160);*/


        generateOne = true;
        engine.get()->updateSpritesInScene();
    }

    ///Call checkCollision method  -->  Clean up
    checkCollision();
    removeCarsOffScreenDown();
    removeTreeTrunksOffScreenDown();
    removeCoinsOffScreenDown();
    if(collision){
        ///END THE GAME AND GO TO END SCREEN WITH SCORE
    }
}

/*
 * for(auto const& value: a) {
 * std::cout << value;
 * ... */


///Check collision between sprites
void GameScreen::checkCollision(){
    ///Check collision with cars --> Death (GAME OVER)
    for(auto &c : cars) {
        if(birdPlayer->getBirdForwardSprite()->collidesWith(*c->getSprite()) ||
           birdPlayer->getbirdForwardMoveSprite()->collidesWith(*c->getSprite()) ||
           birdPlayer->getbirdLeftSprite()->collidesWith(*c->getSprite()) ||
           birdPlayer->getbirdLeftMoveSprite()->collidesWith(*c->getSprite())){

            birdPlayer->score = 69;
            collision = true;
        }
    }
    ///Check collision with treetrunks --> Collision necesarry to cross rivers
    for(auto &t : treeTrunks) { //From most common to least common
        if(birdPlayer->getBirdForwardSprite()->collidesWithTreeTrunk(*t->getSprite())){
            birdPlayer->xPosition = birdPlayer->xPosition - 1;
            birdPlayer->score = birdPlayer->score++;
            birdPlayer->getBirdForwardSprite()->moveTo(birdPlayer->xPosition, birdPlayer->yPosition);
        }
        else if(birdPlayer->getbirdForwardMoveSprite()->collidesWithTreeTrunk(*t->getSprite())){
            birdPlayer->xPosition = birdPlayer->xPosition - 1;
            birdPlayer->score = birdPlayer->score++;
            birdPlayer->getbirdForwardMoveSprite()->moveTo(birdPlayer->xPosition, birdPlayer->yPosition);
        }
        else if(birdPlayer->getbirdLeftSprite()->collidesWithTreeTrunk(*t->getSprite())){
            birdPlayer->xPosition = birdPlayer->xPosition - 1;
            birdPlayer->score = birdPlayer->score++;
            birdPlayer->getbirdLeftSprite()->moveTo(birdPlayer->xPosition, birdPlayer->yPosition);
        }
        else if(birdPlayer->getbirdLeftMoveSprite()->collidesWithTreeTrunk(*t->getSprite())){
            birdPlayer->xPosition = birdPlayer->xPosition - 1;
            birdPlayer->score = birdPlayer->score++;
            birdPlayer->getbirdLeftMoveSprite()->moveTo(birdPlayer->xPosition, birdPlayer->yPosition);
        }
    }
    ///Check collision with coins --> Time off score, erase coin if picked up
    for(auto &c : coins) {
        if(birdPlayer->getBirdForwardSprite()->collidesWith(*c->getSprite()) ||
           birdPlayer->getbirdForwardMoveSprite()->collidesWith(*c->getSprite()) ||
           birdPlayer->getbirdLeftSprite()->collidesWith(*c->getSprite()) ||
           birdPlayer->getbirdLeftMoveSprite()->collidesWith(*c->getSprite())){

            birdPlayer->score = birdPlayer->score + 1000;
            coins.erase(find(coins.begin(), coins.end(), c));

            engine->updateSpritesInScene();
        }
    }
}