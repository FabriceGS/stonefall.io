cmake_minimum_required(VERSION 3.7)
project(stonefall)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Stonefall/main.cpp Stonefall/GridEntity.h Stonefall/GridBlock.cpp Stonefall/GridBlock.h Stonefall/Structure/Base.cpp Stonefall/Structure/Base.h Stonefall/Killable.h)

add_executable(stonefall ${SOURCE_FILES})