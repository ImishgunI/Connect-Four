cmake_minimum_required(VERSION 3.5)

project(Learning)

SET(C_STANDARD_REQUIRED c17)
SET(CXX_STANDARD_REQUIRED c++17)
SET(CMAKE_C_COMPILER /usr/bin/clang)
SET(CMAKE_CXX_COMPILER /usr/bin/clang++)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(main ./src/main.cpp ./src/Board.cpp)

target_link_libraries(main ${SDL2_LIBRARIES})
