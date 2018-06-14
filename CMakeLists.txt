cmake_minimum_required(VERSION 3.7)
project(stonefall)

<<<<<<< HEAD
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Stonefall/main.cpp Stonefall/GridEntity.h Stonefall/GridBlock.cpp Stonefall/GridBlock.h Stonefall/Structure/Base.cpp Stonefall/Structure/Base.h Stonefall/Killable.h)

add_executable(stonefall ${SOURCE_FILES})

set(Poco_DIR /Users/david.oyeka/dev/dev_apps/poco-1.9.0)
set(CMAKE_MODULE_PATH /Users/david.oyeka/dev/dev_apps/poco-1.9.0/cmake-build/Poco/PocoConfig.cmake)

find_package(Poco 1.9.0 COMPONENTS REQUIRED JSON)

if(BOOST_FOUND)
    include_directories(${Poco_INCLUDE_DIRS})
endif()

add_executable(stonefall main.cpp)

if(BOOST_FOUND)
    target_link_libraries(${Poco_LIBRARIES})
endif()
