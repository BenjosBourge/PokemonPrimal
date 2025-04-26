cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME PokemonPrimal)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC
    src/Engine/*.cpp
    src/GUI/*.cpp
)

file ( GLOB CLIENT src/Client/*.cpp )

file ( GLOB SERVER src/Server/*.cpp)


add_executable(${PROJECT_NAME}_Client
        ${SRC}
        ${CLIENT}
)

target_include_directories(${PROJECT_NAME}_Client
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME}_Server
        ${SRC}
        ${SERVER}
)

target_include_directories(${PROJECT_NAME}_Server
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

include(build-SFML.cmake)


