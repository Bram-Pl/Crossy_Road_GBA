//
// Created by pless on 16/12/2020.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <algorithm>
#include <iostream>

#include "GameScreen.h"
#include "../music/InGame.h"
#include "../soundEffects/coinPickUp.h"
#include "../soundEffects/carStopSound.h"
#include "../soundEffects/dropSound.h"

#include "../background/bgGameScreen.c"
#include "carCollisionScene.h"
#include "riverCollisionScene.h"
#include "finishScene.h"

#include "../sprites/shared.c"
#include "../sprites/bird/birdForward.c"
#include "../sprites/bird/birdForwardMove.c"
#include "../sprites/bird/birdLeft.c"
#include "../sprites/bird/birdLeftMove.c"
#include "../sprites/car/Car.c"
#include "../sprites/treetrunk/TreeTrunk.c"
#include "../sprites/coin/coin.c"
#define bgX 0

#pragma region Car Methods
/**
 * @brief detect if car sprites get below GBA_SCREEN_HEIGHT + 32 and remove from vector
 */
void GameScreen::carsBorderDetection(){

    for(auto &c : cars) {
        if(c->x_position < - 32 && !c->switchDir){
            c->x_position = GBA_SCREEN_WIDTH + 32;
        }
        else if(c->x_position > GBA_SCREEN_WIDTH + 32 && c->switchDir){
            c->x_position = -32;
        }
    }

    int sizeOfCars = cars.size();

    cars.erase(
            std::remove_if(cars.begin(), cars.end(), [](std::unique_ptr<car> &c) { return c->isOffScreenDown(); }),
            cars.end());

    if(sizeOfCars > cars.size()){
        engine.get()->updateSpritesInScene();
        ReflipSprite();
    }
}

/**
 * @brief create a single car sprite using template "someCarSprite"
 * @return type car pointer
 */
std::unique_ptr<car> GameScreen::createCar(){
    return std::unique_ptr<car>(new car(builder
    .buildWithDataOf(*someCarSprite.get())));
}
#pragma endregion Cars

#pragma region TreeTrunks Methods
/**
 * @brief detect if treeTrunk sprites get below GBA_SCREEN_HEIGHT + 32 and remove from vector
 */
void GameScreen::treeTrunksBorderDetection() {

    for(auto &t : treeTrunks) {
        if(t->x_position < - 32 && !t->switchDir){
            t->x_position = GBA_SCREEN_WIDTH + 32;
        }
        else if(t->x_position > GBA_SCREEN_WIDTH + 32 && t->switchDir){
            t->x_position = -32;
        }
    }

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

/**
 * @brief create a single TreeTrunk sprite using template "someTreeTrunkSprite"
 * @return type TreeTrunk pointer
 */
std::unique_ptr<treeTrunk> GameScreen::createTreeTrunk(){
    return std::unique_ptr<treeTrunk>(new treeTrunk(builder
        .buildWithDataOf(*someTreeTrunkSprite.get())));
}
#pragma endregion TreeTrunks

#pragma region Coins Methods
/**
 * @brief detect if coins sprites get below GBA_SCREEN_HEIGHT + 32 and remove from vector
 */
 void GameScreen::removeCoinsOffScreenDown() {
    for(auto &c : coins) {
        if(c->isOffScreenDown())
        {
            coins.erase(coins.begin());

            engine->updateSpritesInScene();
            ReflipSprite();
        }
    }
}

/**
 * @brief create a single coin sprite using template "someCoinSprite"
 * @return type coin pointer
 */
std::unique_ptr<coin> GameScreen::createCoin() {
    return std::unique_ptr<coin>(new coin(builder
        .buildWithDataOf(*someCoinSprite.get())));
}
#pragma endregion Coins

#pragma region generic Methods

/**
 * @brief collects sprites in vector
 * @return vector of Sprite type
 */
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

/**
 * @brief collects backgrounds in vector
 * @return vector of Background type
 */
std::vector<Background *> GameScreen::backgrounds() {
    return {
            bgGameScreen.get()
    };
}

/**
 * @brief Flip sprite to their respective state, get corrupted after "updatesSpritesInScene()"
 */
void GameScreen::ReflipSprite() {
    for(auto &c : cars) {
        if(!c->switchDir){
            c->stdMirror = true;
        }
    }
    engine->updateSpritesInScene();
}

#pragma endregion generic Methods

/**
 * @brief method gets called when scene is loaded in
 */
void GameScreen::load() {
    ///Reset engine timer, in case restart from death
    engine->getTimer()->reset();
    ///Disable Background 2 and 3 to prevent gibberish
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1;

    ///Set colour palette for foreground(sprites) and background
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bgGameScreenPal,sizeof(bgGameScreenPal)));

    ///Background parameters
    bgGameScreen = std::unique_ptr<Background>(new Background(1, bgGameScreenTiles, sizeof(bgGameScreenTiles), bgGameScreenMap, sizeof(bgGameScreenMap), MAPLAYOUT_64X32));
    bgGameScreen.get()->useMapScreenBlock(16);
    bgGameScreen->scroll(bgX, bgYPos);

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
    engine->getTimer()->start();
}

/**
 * @brief gets called every tick
 * @param keys
 */
void GameScreen::tick(u16 keys) {
    ///Display the current playtime
    TextStream::instance().setText(std::string("Time:") + engine->getTimer()->to_string(), 4, 8); // 19

    #pragma region movement sprites

    ///BIRD: run tick() for every bird
    birdPlayer->tick(keys);

    ///CARS: run tick() for every car and move their respective Y position according the birds movement
    for(auto &c : cars) {
        c->tick();

        if(globalYPos != birdPlayer->virtualYPos){
            c->y_position = c->y_position + 32;
        }
    }
    ///TREETRUNKS: run tick() for every treetrunk and move their respective Y position according the birds movement
    for(auto &t : treeTrunks) {
        t->tick();

        if(globalYPos != birdPlayer->virtualYPos){
            t->y_position = t->y_position + 32;
        }
    }

    ///COINS: run tick() for every coin and move their respective Y position according the birds movement
    for(auto &c : coins) {
        c->tick();

        if(globalYPos != birdPlayer->virtualYPos){
            c->y_position = c->y_position + 32;
        }
    }

    ///Y Position change for background
    if(globalYPos != birdPlayer->virtualYPos){
        bgYPos = bgYPos - 32;
        bgGameScreen->scroll(bgX, bgYPos);
        birdMoved = true;
        globalYPos = birdPlayer->virtualYPos;
    }

    #pragma endregion movement sprites

    #pragma region generate sprites
    ///GENERATE SPRITES FOR MAP: Call sprites just above the screen to save memory
        if(birdPlayer->virtualYPos == 128 && birdMoved) {
            birdMoved = false;
            ///In order of appearence
            //2nd row
            coins.push_back(createCoin());
            auto &co1 = coins.at(coins.size() - 1);
            co1->setPos(30, 96);

            //3th row
            cars.push_back(createCar());
            auto &c1 = cars.at(cars.size() - 1);
            c1->switchDir = true;
            c1->setPos(-32, (GBA_SCREEN_HEIGHT - 96));
            cars.push_back(createCar());
            auto &c2 = cars.at(cars.size() - 1);
            c2->switchDir = true;
            c2->setPos(38, (GBA_SCREEN_HEIGHT - 96));
            cars.push_back(createCar());
            auto &c3 = cars.at(cars.size() - 1);
            c3->switchDir = true;
            c3->setPos(240, (GBA_SCREEN_HEIGHT - 96));

            //5th row
            treeTrunks.push_back(createTreeTrunk());
            auto &t1 = treeTrunks.at(treeTrunks.size() - 1);
            t1->setPos(GBA_SCREEN_WIDTH, 8);
            treeTrunks.push_back(createTreeTrunk());
            auto &t2 = treeTrunks.at(treeTrunks.size() - 1);
            t2->setPos(GBA_SCREEN_WIDTH + 86, 8);
            treeTrunks.push_back(createTreeTrunk());
            auto &t3 = treeTrunks.at(treeTrunks.size() - 1);
            t3->setPos(GBA_SCREEN_WIDTH + 220, 8);

            //6th row
            coins.push_back(createCoin());
            auto &co2 = coins.at(coins.size() - 1);
            co2->setPos(180, -32);

            birdMoved = false;
            engine.get()->updateSpritesInScene();
            ReflipSprite();
        }
        else if (birdPlayer->virtualYPos == 160 && birdMoved){
            //7th row
            cars.push_back(createCar());
            auto &c4 = cars.at(cars.size() - 1);
            c4->stdMirror = true;
            c4->setPos(-32, -32);
            cars.push_back(createCar());
            auto &c5 = cars.at(cars.size() - 1);
            c5->stdMirror = true;
            c5->setPos(-86, -32);
            cars.push_back(createCar());
            auto &c6 = cars.at(cars.size() - 1);
            c6->stdMirror = true;
            c6->setPos(-350, -32);

            birdMoved = false;
            engine.get()->updateSpritesInScene();
            ReflipSprite();
        }
        else if (birdPlayer->virtualYPos == 192 && birdMoved){
            //8th row
            treeTrunks.push_back(createTreeTrunk());
            auto &t4 = treeTrunks.at(treeTrunks.size()-1);
            t4->setPos(GBA_SCREEN_WIDTH + 32, -24);
            treeTrunks.push_back(createTreeTrunk());
            auto &t5 = treeTrunks.at(treeTrunks.size()-1);
            t5->setPos(GBA_SCREEN_WIDTH + 120, -24);
            treeTrunks.push_back(createTreeTrunk());
            auto &t6 = treeTrunks.at(treeTrunks.size()-1);
            t6->setPos(GBA_SCREEN_WIDTH + 260, -24);

            birdMoved = false;
            engine.get()->updateSpritesInScene();
            ReflipSprite();
        }
        else if (birdPlayer->virtualYPos == 224 && birdMoved){
            //9th row
            coins.push_back(createCoin());
            auto &co3 = coins.at(coins.size()-1);
            co3->setPos(180, -32);

            birdMoved = false;
            engine.get()->updateSpritesInScene();
            ReflipSprite();
        }
        else if (birdPlayer->virtualYPos == 288 && birdMoved){
            //11th row
            cars.push_back(createCar());
            auto &c7 = cars.at(cars.size() - 1);
            c7->switchDir = true;
            c7->setPos(-32, -32);
            cars.push_back(createCar());
            auto &c8 = cars.at(cars.size() - 1);
            c8->switchDir = true;
            c8->setPos(-86, -32);
            cars.push_back(createCar());
            auto &c9 = cars.at(cars.size() - 1);
            c9->switchDir = true;
            c9->setPos(-140, -32);

            birdMoved = false;
            engine.get()->updateSpritesInScene();
            ReflipSprite();
        }
        else if (birdPlayer->virtualYPos == 320 && birdMoved){
            //12th row
            cars.push_back(createCar());
            auto &c10 = cars.at(cars.size() - 1);
            c10->setPos(-32, -32);
            cars.push_back(createCar());
            auto &c11 = cars.at(cars.size() - 1);
            c11->setPos(45, -32);
            cars.push_back(createCar());
            auto &c12 = cars.at(cars.size() - 1);
            c12->setPos(160, -32);

            birdMoved = false;
            engine.get()->updateSpritesInScene();
            ReflipSprite();

        }
        else if (birdPlayer->virtualYPos == 384 && birdMoved){
            //14th row
            treeTrunks.push_back(createTreeTrunk());
            auto &t7 = treeTrunks.at(treeTrunks.size()-1);
            t7->switchDir = true;
            t7->setPos(-40, -24);
            treeTrunks.push_back(createTreeTrunk());
            auto &t8 = treeTrunks.at(treeTrunks.size()-1);
            t8->switchDir = true;
            t8->setPos(80, -24);
            treeTrunks.push_back(createTreeTrunk());
            auto &t9 = treeTrunks.at(treeTrunks.size()-1);
            t9->switchDir = true;
            t9->setPos(200, -24);

            birdMoved = false;
            engine.get()->updateSpritesInScene();
            ReflipSprite();
        }
        else if (birdPlayer->virtualYPos == 416 && birdMoved){
            //15th row
            coins.push_back(createCoin());
            auto &co5 = coins.at(coins.size()-1);
            co5->setPos(200, -32);

            birdMoved = false;
            engine.get()->updateSpritesInScene();
            ReflipSprite();
        }
        else if(birdPlayer->yPosition == 0){ //if bird reaches the end, transistion to finish scene
            engine->getTimer()->stop();

            engine->transitionIntoScene(new finishScene(engine, nCoins, engine->getTimer()->getTotalMsecs()), new FadeOutScene(20));
        }
    #pragma endregion generate sprites

    #pragma region collision methods
    checkCollision();
    carsBorderDetection();
    treeTrunksBorderDetection();
    removeCoinsOffScreenDown();
    #pragma endregion collision methods
}

/**
 * @brief checks collision between bird and car, coins, treetrunks and river stirps (using y-levels)
 */
void GameScreen::checkCollision(){
    ///Check collision with cars, move to car collision scene
    for(auto &c : cars) {
        if(birdPlayer->getBirdForwardSprite()->collidesWithCar(*c->getSprite()) ||
           birdPlayer->getbirdForwardMoveSprite()->collidesWithCar(*c->getSprite()) ||
           birdPlayer->getbirdLeftSprite()->collidesWithCar(*c->getSprite()) ||
           birdPlayer->getbirdLeftMoveSprite()->collidesWithCar(*c->getSprite())){

            engine->enqueueSound(carStopSound, carStopSound_bytes);

            engine->transitionIntoScene(new carCollisionScene(engine), new FadeOutScene(10));
        }
    }

    ///Check collision with treetrunks move bird according the way of the treetrunk
    int i = 0; //increment gets used to count the amount of treetrunks the bird DOESN'T collide with and gets compared with the size of the vector
    for(auto &t : treeTrunks) { //sprite detection from most common to least common
        if(birdPlayer->getBirdForwardSprite()->collidesWithTreeTrunk(*t->getSprite())){
            if(!t->switchDir){
                birdPlayer->xPosition = birdPlayer->xPosition - 1;
            }
            if(t->switchDir){
                birdPlayer->xPosition = birdPlayer->xPosition + 1;
            }
            birdPlayer->getBirdForwardSprite()->moveTo(birdPlayer->xPosition, birdPlayer->yPosition);
        }
        else if(birdPlayer->getbirdForwardMoveSprite()->collidesWithTreeTrunk(*t->getSprite())){
            if(!t->switchDir){
                birdPlayer->xPosition = birdPlayer->xPosition - 1;
            }
            if(t->switchDir){
                birdPlayer->xPosition = birdPlayer->xPosition + 1;
            }
            birdPlayer->getbirdForwardMoveSprite()->moveTo(birdPlayer->xPosition, birdPlayer->yPosition);
        }
        else if(birdPlayer->getbirdLeftSprite()->collidesWithTreeTrunk(*t->getSprite())){
            if(!t->switchDir){
                birdPlayer->xPosition = birdPlayer->xPosition - 1;
            }
            if(t->switchDir){
                birdPlayer->xPosition = birdPlayer->xPosition + 1;
            }
            birdPlayer->getbirdLeftSprite()->moveTo(birdPlayer->xPosition, birdPlayer->yPosition);
        }
        else if(birdPlayer->getbirdLeftMoveSprite()->collidesWithTreeTrunk(*t->getSprite())){
            if(!t->switchDir){
                birdPlayer->xPosition = birdPlayer->xPosition - 1;
            }
            if(t->switchDir){
                birdPlayer->xPosition = birdPlayer->xPosition + 1;
            }
            birdPlayer->getbirdLeftMoveSprite()->moveTo(birdPlayer->xPosition, birdPlayer->yPosition);
        }
        else if(globalYPos == 256 || globalYPos == 352 || birdPlayer->yPosition == 64){ //River strip detection
            i++;
            nTicks++;
            if(nTicks == 64){nTicks = 0;} //Puts delay on detection, just enough to avoid false positives

            if(i == treeTrunks.size()){
                if(nTicks % 8 == 0){
                    engine->enqueueSound(dropSound, dropSound_bytes);
                    engine->transitionIntoScene(new riverCollisionScene(engine), new FadeOutScene(6));
                }
            }
        }
    }

    ///Check collision with coins, erase coin if picked up and remove from screen
    for(auto &c : coins) {
        if(birdPlayer->getBirdForwardSprite()->collidesWith(*c->getSprite()) ||
           birdPlayer->getbirdForwardMoveSprite()->collidesWith(*c->getSprite()) ||
           birdPlayer->getbirdLeftSprite()->collidesWith(*c->getSprite()) ||
           birdPlayer->getbirdLeftMoveSprite()->collidesWith(*c->getSprite())){

            engine->enqueueSound(coinPickUp, coinPickUp_bytes);
            nCoins++;
            coins.erase(coins.begin());
            engine->updateSpritesInScene();
            ReflipSprite();
        }
    }
}