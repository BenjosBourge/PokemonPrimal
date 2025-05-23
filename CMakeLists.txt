cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME PokemonPrimal)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

file( GLOB SRC src/Engine/Entities/*.cpp src/Engine/Systems/*.cpp src/Engine/*.cpp src/Engine/Components/*.cpp
            src/Engine/Maps/*.cpp)

file ( GLOB CLIENT src/Client/*.cpp src/Client/Graph/*.cpp src/Client/Graph/GUI/*.cpp src/Client/Graph/GUI/*.cpp
            src/Client/Scene/*.cpp src/Client/Objects/*.cpp)

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

add_custom_command(
        TARGET ${PROJECT_NAME}_Client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/assets"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}/assets"
)

include(build-SFML.cmake)


