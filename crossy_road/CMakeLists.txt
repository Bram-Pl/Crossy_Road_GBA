project(crossy_road)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp src/HomeStartScene.cpp src/HomeStartScene.h src/GameScreen.cpp src/GameScreen.h src/bird.cpp src/bird.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
