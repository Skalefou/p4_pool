cmake_minimum_required(VERSION 3.10)
project(p4_pool C)

set(CMAKE_C_STANDARD 11)

# Trouver pkg-config
find_package(PkgConfig REQUIRED)

# Chercher les paquets SDL2 et SDL2_image
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_image REQUIRED SDL2_image)

# Inclure les répertoires d'en-tête
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_image_INCLUDE_DIRS})

# Ajouter votre exécutable
add_executable(p4_pool main.c)

# Lier les bibliothèques SDL2 à votre exécutable
target_link_libraries(p4_pool ${SDL2_LIBRARIES} ${SDL2_image_LIBRARIES})