cmake_minimum_required(VERSION 3.1)
project(Battleships)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(WIN32)
    option(SOCKPP_BUILD_SHARED "" OFF)
    option(SOCKPP_BUILD_STATIC "" ON)
endif()

add_subdirectory("dependencies/sockpp")

add_executable(Battleships
    src/main.cpp
)

#Build sockpp
target_include_directories(Battleships PUBLIC ${SOCKPP_INCLUDE_DIR})
if(WIN32)
    message("Building for Win32")

    add_dependencies(Battleships sockpp-static)

    target_link_libraries(Battleships sockpp-static)
    target_link_libraries(Battleships wsock32 ws2_32)
else()
    message("Building for Unix")

    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)

    target_link_libraries(Battleships sockpp Threads::Threads)
endif()
