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
include_directories(./display)
include_directories(/usr/local/include)
include_directories(./external/glew/include)
include_directories(./external/imgui)

set(PROJECT_SOURCES 
    ./main.cpp
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
    ./manager/manager.cpp
    ./utils/my_string.cpp
    ./utils/my_string.h
    ./ui/mainwindow.h
    ./ui/mainwindow.cpp
    ./model/model_loader.h
    ./model/model_transform.h
    ./vertex/edge_array.h
    ./vertex/edge_array.cpp
    ./vertex/edge_loader.cpp
    ./vertex/edge_loader.h
    )

#SDL2

find_library(SDL SDL2)

#SDL2

#GLEW
find_library(GLEW_DYLIB GLEW ${CMAKE_SOURCE_DIR}/external/glew/lib)
add_library(glew SHARED IMPORTED)
set_property(TARGET glew PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/external/glew/lib/libGLEW.dylib)
set_property(TARGET glew PROPERTY IMPORTED_IMPLIB ${GLEW_DYLIB})
#GLEW

# IMGUI

set(imgui_srcs 
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_impl_sdl.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_impl_opengl2.cpp
    )

add_library(imgui STATIC ${imgui_srcs})

target_link_libraries(imgui glew)


# IMGUI

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} imgui glew ${SDL2_LIBRARIES})





