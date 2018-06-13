cmake_minimum_required(VERSION 3.10)
project(stonefall)

set(CMAKE_CXX_STANDARD 17)
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