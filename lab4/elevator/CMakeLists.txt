cmake_minimum_required(VERSION 3.1.0)

project(elevator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

set (SRC
        src/control_panel/control_panel.cpp
        src/control_panel/control_panel.h
        src/cabin/cabin.cpp
        src/cabin/cabin.h
        src/door/door.cpp
        src/door/door.h
        src/elevator/elevator.cpp
        src/elevator/elevator.h
        src/consts/consts.h
        src/constants.h
        )

add_library(${PROJECT_NAME}
        ${SRC}
        ${})

target_include_directories(${PROJECT_NAME} PUBLIC
        ./include/
        ./src/
        )

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})


