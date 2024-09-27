cmake_minimum_required(VERSION 3.10)
project(p4_pool C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_image REQUIRED SDL2_image)
pkg_check_modules(SDL2_net REQUIRED SDL2_net)
pkg_check_modules(SDL2_ttf REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_mixer REQUIRED SDL2_mixer)  # Ajouter SDL2_mixer

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS} ${SDL2_net_INCLUDE_DIRS} ${SDL2_ttf_INCLUDE_DIRS} ${SDL2_mixer_INCLUDE_DIRS})  # Inclure SDL2_mixer

add_executable(p4_pool src/main.c
        src/Window.c
        src/Game.c
        src/Game.h
        src/Window.h
        src/Graphic.c
        src/Map.c
        src/Config.c)

target_link_libraries(p4_pool ${SDL2_LIBRARIES} ${SDL2_image_LIBRARIES} ${SDL2_net_LIBRARIES} ${SDL2_ttf_LIBRARIES} ${SDL2_mixer_LIBRARIES})  # Lier SDL2_mixer