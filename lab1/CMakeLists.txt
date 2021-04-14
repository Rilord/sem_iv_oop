cmake_minimum_required(VERSION 3.0)

project(lab_1 LANGUAGES CXX)

add_definitions(-Wall -Wextra)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(./vertex)
include_directories(./manager)
include_directories(./model)
include_directories(./errors)
include_directories(./ui)
include_directories(./utils)

set(PROJECT_SOURCES 
    ./vertex/vertex.cpp
    ./vertex/edge.cpp
    ./vertex/vertex_array.cpp
    ./vertex/vertex.h
    ./vertex/edge.h
    ./vertex/vertex_array.h
    ./model/model.cpp
    ./model/model.h
    ./model/model_loader.cpp
    ./model/model_transform.cpp
    ./manager/manager.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})





