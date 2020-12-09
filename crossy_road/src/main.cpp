//
// Created by pless on 20/11/2020.
//

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "HomeStartScene.h"

int main(){
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    auto startScene = new HomeStartScene(engine);
    engine->setScene(startScene);

    while (true){
        engine->update();
    }

    return(0);
};