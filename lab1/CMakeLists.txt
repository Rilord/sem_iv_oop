cmake_minimum_required(VERSION 3.0)

project(lab1 VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(app_name "lab1")
add_library(stb INTERFACE)


if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message("Good choice, buddy!")

endif()
if (UNIX)

##########


# OpenGL

find_package(OpenGL REQUIRED)

if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
endif()


# GLEW 

#find_library(GLEW_DYLIB GLEW ${CMAKE_SOURCE_DIR}/external/glew/lib)
#add_library(glew SHARED IMPORTED)
#set_property(TARGET glew PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/external/glew/lib/libGLEW.2.2.0.dylib)
#set_property(TARGET glew PROPERTY IMPORTED_IMPLIB ${GLEW_DYLIB})


find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

######

#GLFW

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw)

set(app_includes ${app_includes} ${CMAKE_SOURCE_DIR}/external/glfw/include/)

set(app_libs ${app_libs} glfw ${GLFW_LIBRARIES})



#####

# IMGUI 
set(imgui_srcs 
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_impl_opengl3.cpp
    )

add_library(imgui STATIC ${imgui_srcs})

target_link_libraries(imgui glew)

target_include_directories(imgui PUBLIC
    ${CMAKE_SOURCE_DIR}/external/imgui/
    ${CMAKE_SOURCE_DIR}/external/glew/include/
    ${CMAKE_SOURCE_DIR}/external/glfw/include/
    )

set(app_includes ${app_includes}
    ${CMAKE_SOURCE_DIR}/external/imgui
    )
########## IMPLOT

set(implot_srcs
    ${CMAKE_SOURCE_DIR}/external/implot/implot_items.cpp
    ${CMAKE_SOURCE_DIR}/external/implot/implot.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_impl_opengl3.cpp
    )

add_library(implot STATIC ${implot_srcs})


target_include_directories(implot PUBLIC
    ${CMAKE_SOURCE_DIR}/external/imgui/
    ${CMAKE_SOURCE_DIR}/external/implot/
    ${CMAKE_SOURCE_DIR}/external/glew/include/
    ${CMAKE_SOURCE_DIR}/external/glfw/include/
    )


##########


set(app_includes ${app_includes}
    ${CMAKE_SOURCE_DIR}/external/imgui
    )

set(app_includes ${app_includes}
    ${CMAKE_SOURCE_DIR}/external/implot
    )
set(app_libs ${app_libs} imgui)
set(app_libs ${app_libs} implot)
##########



# 3D RENDERER


file (GLOB app_srcs
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    )

set(app_include ${CMAKE_SOURCE_DIR}/include ${app_includes})

###########

# executable

set(app_libs ${app_libs} ${OPENGL_LIBRARY})

add_executable(${app_name}  ${app_srcs})

target_include_directories(${app_name} PUBLIC ${app_includes})


target_link_libraries(${app_name} ${app_libs})

endif ()
