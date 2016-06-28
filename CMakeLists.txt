cmake_minimum_required(VERSION 3.5)
project(Game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp entity.cpp entity.h Player.cpp Player.h projectile.cpp projectile.h Enemy.cpp Enemy.h randoms.h randoms.cpp randoms.h textDisplay.cpp textDisplay.h Wall.cpp Wall.h Organism.cpp Organism.h)
add_executable(Game ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Game ${SFML_LIBRARIES})
endif()

include_directories(.)