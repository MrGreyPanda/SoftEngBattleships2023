cmake_minimum_required(VERSION 3.1)
project(battleships)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(WIN32)
    option(SOCKPP_BUILD_SHARED "" OFF)
    option(SOCKPP_BUILD_STATIC "" ON)
endif()

# enable testing
include(CTest)
include(GoogleTest)
enable_testing()

# TODO ONLY RUN IF NOT PROD
# Enable code coverage
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")
endif()
set(CMAKE_BUILD_TYPE Debug)


add_subdirectory(dependencies/sockpp)
add_subdirectory(dependencies/json)
add_subdirectory(dependencies/googletest)

# Include header files
include_directories(include)

# find source files
file(GLOB_RECURSE COMMON_SOURCES src/common/*.cpp)

file(GLOB_RECURSE CLIENT_SOURCES src/client/*.cpp)
list(FILTER CLIENT_SOURCES EXCLUDE REGEX ".*src/client/main\\.cpp$")

file(GLOB SERVER_SOURCES src/server/*.cpp)
list(FILTER SERVER_SOURCES EXCLUDE REGEX ".*src/server/main\\.cpp$")

file(GLOB TEST_SOURCES tests/*.test.cpp)

# build client
add_executable(Battleships ${COMMON_SOURCES} src/client/main.cpp ${CLIENT_SOURCES})

# build server
add_executable(BattleshipsServer ${COMMON_SOURCES} src/server/main.cpp ${SERVER_SOURCES})

add_executable(BattleshipsTests ${COMMON_SOURCES} ${CLIENT_SOURCES} ${SERVER_SOURCES} ${TEST_SOURCES})


# Build sockpp
target_include_directories(Battleships PUBLIC ${SOCKPP_INCLUDE_DIR})
target_include_directories(BattleshipsServer 
    PUBLIC ${SOCKPP_INCLUDE_DIR})
target_include_directories(BattleshipsTests 
    PUBLIC ${SOCKPP_INCLUDE_DIR}

)
if(WIN32)
    message("Building for Win32")

    add_dependencies(Battleships sockpp-static)
    target_link_libraries(Battleships sockpp-static wsock32 ws2_32)
    
    add_dependencies(BattleshipsServer sockpp-static)
    target_link_libraries(BattleshipsServer sockpp-static wsock32 ws2_32)

    add_dependencies(BattleshipsTests sockpp-static)
    target_link_libraries(BattleshipsTests sockpp-static wsock32 ws2_32)
else()
    message("Building for Unix")

    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)

    target_link_libraries(Battleships sockpp Threads::Threads)
    target_link_libraries(BattleshipsServer sockpp Threads::Threads)
    target_link_libraries(BattleshipsTests sockpp Threads::Threads)
endif()

# Build json
add_dependencies(Battleships nlohmann_json)
add_dependencies(BattleshipsServer nlohmann_json)

target_include_directories(Battleships PUBLIC ${NLOHMANN_JSON_INCLUDE_BUILD_DIR})
target_link_libraries(Battleships nlohmann_json)

target_include_directories(BattleshipsServer PUBLIC ${NLOHMANN_JSON_INCLUDE_BUILD_DIR})
target_link_libraries(BattleshipsServer nlohmann_json gtest gtest_main gmock gmock_main)

target_include_directories(BattleshipsTests PUBLIC ${NLOHMANN_JSON_INCLUDE_BUILD_DIR})
target_link_libraries(BattleshipsTests nlohmann_json gtest gtest_main gmock gmock_main)

gtest_discover_tests(BattleshipsTests)
