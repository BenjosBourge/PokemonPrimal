cmake_minimum_required(VERSION 3.16)
project(GraphSFML LANGUAGES CXX)

if (APPLE)
    cmake_policy(SET CMP0135 NEW)
endif()

if (UNIX)
    set(CMAKE_CXX_FLAGS "-g3 -O2")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS "-O2 /EHsc")
endif() # set extra flags

option(SFMLCPM "Download SFML with CPM instead of FetchContent" ON)

option(
    SFML_CPM_COMPATIBILITY
    "Should SFML be declared with FetchContent functions to be compatible. This doesn't not allow CPM cache to work."
    ON
)

include(FetchContent)

# Use CPM for SFML
FetchContent_Declare(
    sfml
    URL https://github.com/SFML/SFML/archive/refs/tags/2.6.1.zip
)
FetchContent_MakeAvailable(sfml)

file(GLOB SOURCES "*.cpp")

add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Link against SFML
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

if (WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/_deps/sfml-build/lib/Debug/ ${CMAKE_BINARY_DIR}/
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/_deps/sfml-src/extlibs/bin/x64/ ${CMAKE_BINARY_DIR}/
    )
endif()
