//
// Created by 11700372 on 17/12/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BIOMES_H
#define GBA_SPRITE_ENGINE_PROJECT_BIOMES_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>

using namespace std;

///biomes .h file
class biomes {
private:
    ///Declaration of sprites
    unique_ptr<Sprite> grassSprite;
    unique_ptr<Sprite> roadSprite;
    unique_ptr<Sprite> waterSprite;

    ///timer for the slide 'animation'
    int timer{};

public:
    ///Constructor
    biomes(unique_ptr<Sprite> grassSprite,
           unique_ptr<Sprite> roadSprite,
           unique_ptr<Sprite> waterSprite
           ) :
            grassSprite(move(grassSprite)),
            roadSprite(move(roadSprite)),
            waterSprite(move(waterSprite)) {};

    ///Getters
    Sprite *getGrassSprite() { return grassSprite.get(); }

    Sprite *getRoadSprite() { return roadSprite.get(); }

    Sprite *getWaterSprite() { return waterSprite.get(); }

    ///Tick function for key presses
    void tick(u16 keys);

    ///Declaration start position of new biomes
    double xPosition = (GBA_SCREEN_WIDTH/2);
    double yPosition = (GBA_SCREEN_HEIGHT + (2*32)); //2 verhogen voor gewenste start pos

};


#endif //GBA_SPRITE_ENGINE_PROJECT_BIOMES_H
