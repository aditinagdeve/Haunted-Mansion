cmake_minimum_required(VERSION 3.16)

project(HauntedMansion LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(HauntedMansion
    main.cpp
    src/Game.cpp
    src/Room.cpp
    src/Player.cpp
    src/Ghost.cpp
    src/item.cpp
    src/puzzle.cpp
)

target_include_directories(HauntedMansion PRIVATE
    include
)
