project(crossy_road)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp src/HomeStartScene.cpp src/HomeStartScene.h src/GameScreen.cpp src/GameScreen.h src/sprites/bird.cpp src/sprites/bird.h src/sprites/car.cpp src/sprites/car.h src/sprites/treeTrunk.cpp src/sprites/treeTrunk.h src/sprites/coin.cpp src/sprites/coin.h src/carCollisionScene.cpp src/carCollisionScene.h src/riverCollisionScene.cpp src/riverCollisionScene.h src/finishScene.cpp src/finishScene.h background/startscreen.c)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
