cmake_minimum_required(VERSION 3.19)
project(lab_3)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)


add_executable(lab_3 main.cpp
        qt/mainwindow.h
        qt/mainwindow.cpp
        qt/qt_render.h
        qt/qt_render.cpp
        qt/qt_render_factory.h
        qt/qt_render_factory.cpp
        )

target_include_directories(${PROJECT_NAME} PRIVATE
        ./engine/
        ./qt/
        )

add_subdirectory(engine)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED} engine)

