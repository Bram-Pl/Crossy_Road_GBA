//
// Created by pless on 20/11/2020.
//

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "HomeStartScene.h"

int main(){
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    ///Call scene for the start menu 'HomeStartScene'
    auto* startScene = new HomeStartScene(engine);
    engine->setScene(startScene);

    ///Neverending loop to update engine
    while (true){
        engine->update();
        engine->delay(1000);
    }
};