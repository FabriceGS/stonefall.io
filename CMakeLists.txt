cmake_minimum_required(VERSION 3.10)
project(stonefall)

set(CMAKE_CXX_STANDARD 17)
set(Poco_DIR /Users/david.oyeka/dev/dev_apps/poco-1.9.0/cmake-build/Poco)

find_package(Poco 1.9.0 COMPONENTS REQUIRED JSON Net Util XML)

include_directories(/Users/david.oyeka/dev/dev_apps/poco-1.9.0)
link_libraries(${Poco_LIBRARIES})

add_executable(stonefall main.cpp)

target_link_libraries(stonefall)