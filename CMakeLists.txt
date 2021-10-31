cmake_minimum_required(VERSION 3.16)
project(blasteroids C)

set(CMAKE_C_STANDARD 99)

add_executable(game game.c utils.c linkedList.c ship.c blast.c asteroid.c asteroid_list.c blast_list.c)

if (WIN32)
    #     TODO.
else (APPLE)
    set(ALLEGRO_INCLUDE "/usr/local/include")
    set(ALLEGRO_LIB "/usr/local/lib")
    set(ALLEGRO_DYLIB "/usr/local/lib/*allegro*.dylib")
endif ()

include_directories(${ALLEGRO_INCLUDE})
link_directories(${ALLEGRO_LIB})
file(GLOB LIBRARIES "${ALLEGRO_DYLIB}")

target_link_libraries(game ${LIBRARIES})
