cmake_minimum_required(VERSION 3.16)
project(R-Type)

########### R-Type Standard ###########

set(CMAKE_CXX_STANDARD 20)

if (UNIX)
    set(CMAKE_CXX_FLAGS "-g3 -O2")
elseif(WIN32)
    set(CMAKE_CXX_FLAGS "-O2 /EHsc")
endif()

if (UNIX)
    if (DEFINED CLANG)
        find_program(TIDY "clang-tidy")

        if (TIDY)
            set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
        endif()
    endif()
endif()

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

add_subdirectory(src/Error)
add_subdirectory(src/Graph)
add_subdirectory(src/CtrlC)

########### R-Type Server ###########

set(RTYPE_SERVER r-type_server) # will be the bin created at the end
set(SERVER_DIR src/Server) # server dir containing the server files
set(ENGINE_DIR src/Engine) # server dir containing the engine files

file(GLOB_RECURSE RTYPE_SERVER_SRC
    ${SERVER_DIR}/*.cpp
    ${ENGINE_DIR}/*.cpp
) # kind of wildcard here

# create the "r-type_server" binary
add_executable(${RTYPE_SERVER} ${RTYPE_SERVER_SRC})

if (WIN32)
    target_link_libraries(${RTYPE_SERVER} wsock32 ws2_32) # support for windows
endif()

set_property(TARGET ${RTYPE_SERVER} PROPERTY CXX_STANDARD 20)
target_compile_options(${RTYPE_SERVER} PUBLIC ${CXX_FLAGS})

target_link_libraries(${RTYPE_SERVER} Error GraphSFML CtrlC)
target_include_directories(${RTYPE_SERVER} PRIVATE include)

########### R-Type Client ###########

set(RTYPE_CLIENT r-type_client) # will be the bin created at the end
set(CLIENT_DIR src/Client) # server dir containing the files

file(GLOB RTYPE_CLIENT_SRC
    ${CLIENT_DIR}/*.cpp
) # kind of wildcard here

add_executable(${RTYPE_CLIENT} ${RTYPE_CLIENT_SRC})

set_property(TARGET ${RTYPE_CLIENT} PROPERTY CXX_STANDARD 20)
target_compile_options(${RTYPE_CLIENT} PUBLIC ${CXX_FLAGS})

target_link_libraries(${RTYPE_CLIENT} Error GraphSFML CtrlC)

target_include_directories(${RTYPE_CLIENT} PRIVATE include)

########### R-Type Packing ###########

include(CPack)

set(CPACK_GENERATOR ZIP)
set(CPACK_PACKAGE_FILE_NAME "R-Type")

# Include the executable binaries in the package
install(TARGETS ${RTYPE_SERVER} ${RTYPE_CLIENT}
    RUNTIME DESTINATION bin
)

if (WIN32)
    # Copy executables from Debug folder to main build folder
    add_custom_command(TARGET ${RTYPE_SERVER} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${RTYPE_SERVER}> ${CMAKE_BINARY_DIR}/
    )
    add_custom_command(TARGET ${RTYPE_CLIENT} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${RTYPE_CLIENT}> ${CMAKE_BINARY_DIR}/
    )

    # Remove the out directory after build
    add_custom_command(TARGET ${RTYPE_SERVER} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/out/
    )

    install(FILES ${CMAKE_BINARY_DIR}/Release/GraphSFML.dll
        DESTINATION bin
        CONFIGURATIONS Release
    )
endif()

# Include the header files and other necessary files
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
)

# Set CPack options
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

########### R-Type Tests ###########

set(TEST_DIR r-type_tests)

if (DEFINED TESTS)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        SOURCE_DIR ${CMAKE_BINARY_DIR}/googletest-src
    )

    FetchContent_GetProperties(googletest)

    if (NOT googletest_POPULATED)
        FetchContent_Populate(googletest)
        add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src ${CMAKE_BINARY_DIR}/googletest-build)
    endif()

    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fprofile-arcs -ftest-coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    endif()

    file(GLOB TESTS_SRC
        tests/*.cpp
    )

    list(APPEND TESTS_SRC
        src/Client/ClientConnection.cpp
    )

    add_executable(${TEST_DIR} ${TESTS_SRC})

    target_link_libraries(${TEST_DIR} Error GraphSFML CtrlC gtest gtest_main gmock pthread)

    target_include_directories(${TEST_DIR} PRIVATE include)
    target_include_directories(${TEST_DIR} PRIVATE ${CMAKE_BINARY_DIR}/googletest-src/googletest/include)
    target_include_directories(${TEST_DIR} PRIVATE ${CMAKE_BINARY_DIR}/googletest-src/googlemock/include)
endif()
