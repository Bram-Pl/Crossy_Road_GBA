//
// Created by pless on 16/12/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GAMESCREEN_H
#define GBA_SPRITE_ENGINE_PROJECT_GAMESCREEN_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>

#include "sprites/bird.h"
#include "sprites/car.h"
#include "sprites/treeTrunk.h"
#include "sprites/coin.h"

class GameScreen : public Scene {
private:
    ///Declaration of background and sprites
    std::unique_ptr<Background> bgGameScreen;
    std::unique_ptr<bird> birdPlayer;

    ///Create spritebuilder to create sprites
    SpriteBuilder <Sprite> builder;

    ///CARS: Sprites and methods
    std::unique_ptr<Sprite> someCarSprite;
    std::vector<std::unique_ptr<car>> cars;
    std::unique_ptr<car> createCar();
    void carsBorderDetection();

    ///TREETRUNK: Sprites and methods
    std::unique_ptr<Sprite> someTreeTrunkSprite;
    std::vector<std::unique_ptr<treeTrunk>> treeTrunks;
    std::unique_ptr<treeTrunk> createTreeTrunk();
    void treeTrunksBorderDetection();

    ///COIN: Sprites and methods
    std::unique_ptr<Sprite> someCoinSprite;
    std::vector<std::unique_ptr<coin>> coins;
    std::unique_ptr<coin> createCoin();
    void removeCoinsOffScreenDown();

    ///Extra methods
    void ReflipSprite();
    void checkCollision();

    ///Extra variables
    bool birdMoved = true;
    int globalYPos = (GBA_SCREEN_HEIGHT - 32);
    int bgYPos = 352;
    int nTicks = 0;
    unsigned char nCoins = 0;

public:
    ///Constructor
    GameScreen(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    ///Getters
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    ///Other
    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_GAMESCREEN_H
