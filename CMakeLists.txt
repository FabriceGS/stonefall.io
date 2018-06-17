cmake_minimum_required(VERSION 3.7)
project(stonefall)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Stonefall/main.cpp Stonefall/GridEntity.h Stonefall/GridBlock.cpp Stonefall/GridBlock.h Stonefall/Structure/Base.cpp Stonefall/Structure/Base.h Stonefall/Killable.h)

set(Poco_DIR ~/dev/dev_apps/poco-1.9.0/cmake-build/Poco/)

find_package(Poco 1.9.0 COMPONENTS REQUIRED JSON Net Util XML)

include_directories(~/dev/dev_apps/poco-1.9.0)
link_libraries(${Poco_LIBRARIES})

add_executable(stonefall ${SOURCE_FILES})

target_link_libraries(stonefall)