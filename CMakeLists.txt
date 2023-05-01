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

add_executable(server_tests
    # Header files from common
    src/common/network/requests/client_request.h
    src/common/network/responses/server_response.h
    src/common/helpers/helper_functions.h
    src/common/game_state/include/ship.h
    src/common/game_state/include/board.h
    src/common/game_state/include/player.h
    src/common/game_state/include/game_state.h

    # Header files from server
    src/server/server_network_manager.h
    src/server/game_instance_manager.h
    src/server/game_instance.h
    src/server/player_manager.h

    # Source files from common
    src/common/network/requests/client_request.cpp
    src/common/network/responses/server_response.cpp
    src/common/helpers/helper_functions.cpp
    src/common/game_state/ship.cpp
    src/common/game_state/board.cpp
    src/common/game_state/player.cpp
    src/common/game_state/game_state.cpp

    # Source files from server
    src/server/server_network_manager.cpp
    src/server/game_instance_manager.cpp
    src/server/game_instance.cpp
    src/server/player_manager.cpp

    # Test Sources
    src/server/tests/player_manager.test.cpp
    src/server/tests/game_instance.test.cpp
    src/server/tests/game_instance_manager.test.cpp
)


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
target_link_libraries(BattleshipsServer nlohmann_json)

target_include_directories(BattleshipsTests PUBLIC ${NLOHMANN_JSON_INCLUDE_BUILD_DIR})
target_link_libraries(BattleshipsTests nlohmann_json gtest gtest_main gmock gmock_main)


include(GoogleTest)
gtest_discover_tests(BattleshipsTests)
