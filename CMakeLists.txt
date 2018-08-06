cmake_minimum_required(VERSION 3.8)
project(stonefall)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_CFLAGS} -fopenmp")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")

set(SOURCE_FILES
        src/cpp/AbstractClasses/GridEntity.h src/cpp/Map/GridBlock.cpp src/cpp/Map/GridBlock.h
        src/cpp/Structure/Base.cpp src/cpp/Structure/Base.h src/cpp/AbstractClasses/Killable.h
        src/cpp/Server/PageRequestHandler.cpp src/cpp/Server/PageRequestHandler.h
        src/cpp/Server/WebSocketRequestHandler.cpp src/cpp/Server/WebSocketRequestHandler.h src/cpp/Structure/Mine.cpp
        src/cpp/Structure/Mine.h src/cpp/Structure/Resource.cpp src/cpp/Structure/Resource.h
        src/cpp/Structure/Turret.cpp src/cpp/Structure/Turret.h src/cpp/Structure/Wall.cpp src/cpp/Structure/Wall.h
        src/cpp/Unit/Attacker.cpp src/cpp/Unit/Attacker.h src/cpp/Map/Grid.cpp src/cpp/Game/Game.cpp src/cpp/Game/Game.h
        src/cpp/Game/Player.cpp src/cpp/Game/Player.h src/cpp/Server/RequestHandlerFactory.cpp
        src/cpp/Game/GameState.cpp src/cpp/Game/GameState.h
        src/cpp/Server/RequestHandlerFactory.h src/cpp/Map/Grid.h src/cpp/Pathing/AStar.cpp src/cpp/Pathing/AStar.h src/cpp/Config/Utility.h)

set(Poco_DIR ~/dev/dev_apps/poco-1.9.0/cmake_build/Poco/)

find_package(Poco 1.9.0 COMPONENTS REQUIRED JSON Net Util XML)

include_directories(~/dev/dev_apps/poco-1.9.0 src/cpp)
link_libraries(${Poco_LIBRARIES})

add_executable(stonefall src/cpp/Main/main.cpp src/cpp/Config/ReleaseConstants.h ${SOURCE_FILES})
add_executable(stonefall-test src/cpp/Test/Catch.h src/cpp/Config/TestConstants.h src/cpp/Test/Test.cpp ${SOURCE_FILES})

target_link_libraries(stonefall)