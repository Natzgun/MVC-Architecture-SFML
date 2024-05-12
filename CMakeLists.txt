cmake_minimum_required(VERSION 3.25)
project(Revolution_Game)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Variables para fuentes cpp y cabeceras
set(MODEL_SOURCES
        Model/Model.cpp Model/Model.h)

set(VIEW_SOURCES
        View/View.cpp View/View.h)

set(CONTROLLER_SOURCES
        Controller/Controller.cpp Controller/Controller.h)

# Agregar ejecutable
add_executable(Revolution_Game
        "main.cpp"
        ${MODEL_SOURCES}
        ${VIEW_SOURCES}
        ${CONTROLLER_SOURCES})

target_link_libraries(Revolution_Game
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        sfml-network
        )

