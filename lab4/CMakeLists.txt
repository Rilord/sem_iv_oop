cmake_minimum_required(VERSION 3.1.6)
project(lab_4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

add_executable(${PROJECT_NAME}
        ./main.cpp
        src/ui/mainwindow.h
        src/ui/mainwindow.cpp
        )

target_include_directories(${PROJECT_NAME} PRIVATE
        ./elevator/src
        ./src/
        )

add_subdirectory(./elevator)

 