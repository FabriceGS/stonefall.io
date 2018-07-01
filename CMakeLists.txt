cmake_minimum_required(VERSION 3.7)
project(stonefall)

set(CMAKE_CXX_STANDARD 11)

set(MY_VAR "hello")

set(SOURCE_FILES
        src/cpp/main.cpp src/cpp/Interfaces/GridEntity.h src/cpp/GridBlock.cpp src/cpp/GridBlock.h src/cpp/Structure/Base.cpp src/cpp/Structure/Base.h src/cpp/Interfaces/Killable.h src/cpp/Server/PageRequestHandler.cpp src/cpp/Server/PageRequestHandler.h src/cpp/Server/WebSockets.cpp src/cpp/Server/WebSockets.h src/cpp/Structure/Mine.cpp src/cpp/Structure/Mine.h src/cpp/Constants.h src/cpp/Structure/Resource.cpp src/cpp/Structure/Resource.h src/cpp/Structure/Turret.cpp src/cpp/Structure/Turret.h src/cpp/Structure/Wall.cpp src/cpp/Structure/Wall.h src/cpp/Unit/Attacker.cpp src/cpp/Unit/Attacker.h)

set(Poco_DIR ~/dev/dev_apps/poco-1.9.0/cmake_build/Poco/)

find_package(Poco 1.9.0 COMPONENTS REQUIRED JSON Net Util XML)

include_directories(~/dev/dev_apps/poco-1.9.0)
link_libraries(${Poco_LIBRARIES})

add_executable(stonefall ${SOURCE_FILES})

target_link_libraries(stonefall)