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
enable_testing()

add_subdirectory(dependencies/sockpp)
add_subdirectory(dependencies/json)
add_subdirectory(dependencies/googletest)

# Include header files
include_directories(include)

# find source files
file(GLOB COMMON_SOURCES src/common/*.cpp)
file(GLOB CLIENT_SOURCES src/client/*.cpp)
file(GLOB SERVER_SOURCES src/server/*.cpp)
file(GLOB TEST_SOURCES tests/*.cpp)

# build client
add_executable(Battleships ${COMMON_SOURCES} ${CLIENT_SOURCES})

# build server
add_executable(BattleshipsServer ${COMMON_SOURCES} ${SERVER_SOURCES})

add_executable(BattleshipsTests ${COMMON_SOURCES} ${CLIENT_SOURCES} ${SERVER_SOURCES} ${TEST_SOURCES})


# Build sockpp
target_include_directories(Battleships PUBLIC ${SOCKPP_INCLUDE_DIR})
target_include_directories(BattleshipsServer 
    PUBLIC ${SOCKPP_INCLUDE_DIR}
)
if(WIN32)
    message("Building for Win32")

    add_dependencies(Battleships sockpp-static)
    target_link_libraries(Battleships sockpp-static)
    target_link_libraries(Battleships wsock32 ws2_32)
    
    add_dependencies(BattleshipsServer sockpp-static)
    target_link_libraries(BattleshipsServer sockpp-static)
    target_link_libraries(BattleshipsServer wsock32 ws2_32)
else()
    message("Building for Unix")

    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)

    target_link_libraries(Battleships sockpp Threads::Threads)
    target_link_libraries(BattleshipsServer sockpp Threads::Threads)
endif()

# Build json
add_dependencies(Battleships nlohmann_json)
add_dependencies(BattleshipsServer nlohmann_json)

target_include_directories(Battleships PUBLIC ${NLOHMANN_JSON_INCLUDE_BUILD_DIR})
target_link_libraries(Battleships nlohmann_json)

target_include_directories(BattleshipsServer PUBLIC ${NLOHMANN_JSON_INCLUDE_BUILD_DIR})
target_link_libraries(BattleshipsServer nlohmann_json)

target_include_directories(BattleshipsTests PUBLIC ${NLOHMANN_JSON_INCLUDE_BUILD_DIR})
target_link_libraries(BattleshipsTests nlohmann_json gtest gtest_main gmock gmock_main)


include(GoogleTest)
gtest_discover_tests(BattleshipsTests)
