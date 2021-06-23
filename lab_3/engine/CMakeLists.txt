cmake_minimum_required(VERSION 3.1.6)

project(engine)

set(CMAKE_CXX_STANDARD 20)

set(OBJECT_SOURCES
        objects/object.h
        objects/camera/camera.h
        objects/camera/camera.cpp
        objects/composite/composite.h
        objects/composite/composite.cpp
        objects/model/model.h
        objects/model/model.cpp
        objects/model/edge.cpp
        objects/model/edge.h
        objects/model/mesh.cpp
        objects/model/mesh.h
        objects/model/polygon.cpp
        objects/model/polygon.h
        objects/model/vertex.cpp
        objects/model/vertex.h
        scene/scene.h
        scene/scene.cpp
        objects/matrix.cpp objects/matrix.h)

set(MANAGER_SOURCES
        managers/base_manager.h
        managers/load_manager.cpp
        managers/load_manager.h
        managers/load_manager_creator.cpp
        managers/load_manager_creator.h
        managers/render_manager.cpp
        managers/render_manager.h
        managers/render_manager_creator.cpp
        managers/render_manager_creator.h
        managers/scene_manager.cpp
        managers/scene_manager.h
        managers/scene_manager_creator.cpp
        managers/scene_manager_creator.h
        managers/transform_manager.cpp
        managers/transform_manager.h
        managers/transform_manager_creator.cpp
        managers/transform_manager_creator.h
        )

set(LOAD_CONTROLLER_SOURCES
        load_controller/abstract_load_controller.cpp
        load_controller/abstract_load_controller.h
        load_controller/model_load_controller.cpp
        load_controller/model_load_controller.h
        load_controller/model_load_controller_creator.cpp
        load_controller/model_load_controller_creator.h
        load_controller/scene_load_controller.cpp
        load_controller/scene_load_controller.h
        load_controller/scene_load_controller_creator.cpp
        load_controller/scene_load_controller_creator.h
        )

set(LOADER_SOURCES
        loader/base_loader.h
        loader/base_model_loader.h
        loader/base_scene_loader.h
        loader/file_camera_loader.cpp
        loader/file_camera_loader.h
        loader/file_model_loader.cpp
        loader/file_model_loader.h
        loader/file_scene_loader.cpp
        loader/file_scene_loader.h
        )

set(FACADE
        facade/facade.cpp
        facade/facade.h
        )

set(BUILDER_SOURCES
        builder/base_builder.h
        builder/camera_builder.cpp
        builder/camera_builder.h
        builder/model_builder.cpp
        builder/model_builder.h
        builder/scene_builder.cpp
        builder/scene_builder.h
        )

set(ERRORS
        errors/errors.h
        error.h)

set(COMMANDS_SOURCES
        commands/base_command.h
        commands/camera_command.cpp
        commands/model_command.cpp
        commands/scene_command.cpp
        commands/camera_command.h
        commands/model_command.h
        commands/scene_command.h
        )

set(CONFIG
        config/abstract_config.h
        config/config_creator.cpp
        config/config_creator.h
        config/libconf_config.cpp
        config/libconf_config.h
        )

set(RENDER
        renderer/abstract_renderer.h)


add_library(config++ SHARED IMPORTED)
set_target_properties(config++ PROPERTIES
        IMPORTED_LOCATION "/usr/local/opt/libconfig/lib/libconfig++.a"
        INTERFACE_INCLUDE_DIRECTORIES "/usr/local/opt/libconfig/include/"
        )

add_library(${PROJECT_NAME}
        ${OBJECT_SOURCES}
        ${MANAGER_SOURCES}
        ${LOADER_SOURCES}
        ${LOAD_CONTROLLER_SOURCES}
        ${FACADE}
        ${BUILDER_SOURCES}
        ${COMMANDS_SOURCES}
        ${RENDER}
        ${ERRORS}
        ${CONFIG}
        ${SPECTATOR_SOURCES}
        )


target_include_directories(${PROJECT_NAME} PUBLIC ./ /usr/local/include/)

target_link_libraries(${PROJECT_NAME} config++)