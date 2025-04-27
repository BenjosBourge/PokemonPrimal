cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME PokemonPrimal)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

file( GLOB SRC src/Engine/Entities/*.cpp src/Engine/Systems/*.cpp src/Engine/*.cpp)

file ( GLOB CLIENT src/Client/*.cpp src/Client/Graph/*.cpp)

file ( GLOB SERVER src/Server/*.cpp)


add_executable(${PROJECT_NAME}_Client
        ${SRC}
        ${CLIENT}
)

target_include_directories(${PROJECT_NAME}_Client
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include/Core
        ${CMAKE_SOURCE_DIR}/include/Client
)

add_executable(${PROJECT_NAME}_Server
        ${SRC}
        ${SERVER}
)

target_include_directories(${PROJECT_NAME}_Server
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include/Core
        ${CMAKE_SOURCE_DIR}/include/Server
)

include(build-SFML.cmake)


