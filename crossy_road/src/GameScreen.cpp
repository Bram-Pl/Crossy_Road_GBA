//
// Created by pless on 16/12/2020.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include "GameScreen.h"

std::vector<Background *> GameScreen::backgrounds() {
    return {
        bgBasic.get()
    };
}

std::vector<Sprite *> GameScreen::sprites() {
    return{};
}

void GameScreen::load() { //what to do upon loading
    TextStream::instance().setText("Test Fase", 16, 9);

    SpriteBuilder<Sprite> builder;

    //birdUP = builder;
}

void GameScreen::tick(u16 keys) {

}