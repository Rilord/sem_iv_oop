cmake_minimum_required(VERSION 3.0)

project(lab2 VERSION 0.1 LANGUAGES CXX)



 
add_definitions(-Wall -Wextra)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/gtest)
find_package(Threads REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/Set)
include_directories(${CMAKE_SOURCE_DIR}/tests)


file(GLOB test_sources
    "tests/*.hpp"
    )

set(lib_sources
               ${CMAKE_SOURCE_DIR}/Set/node.h
               ${CMAKE_SOURCE_DIR}/Set/init.cpp
               ${CMAKE_SOURCE_DIR}/Set/node_implementation.hpp
               ${CMAKE_SOURCE_DIR}/Set/set_iterator.h
               ${CMAKE_SOURCE_DIR}/Set/set_iterator_implementaition.hpp
               ${CMAKE_SOURCE_DIR}/Set/set.h
               ${CMAKE_SOURCE_DIR}/Set/set_implementation.hpp
               ${CMAKE_SOURCE_DIR}/Set/exceptions.h
               )


include_directories(${CMAKE_SOURCE_DIR}/external/gtest/googletest/include)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/main.cpp ${test_sources} ${lib_sources})

target_link_libraries(${PROJECT_NAME} gtest Threads::Threads)

enable_testing()
