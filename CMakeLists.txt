cmake_minimum_required(VERSION 3.25)
project(Revolution_Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Incluir la carpeta de cabeceras
include_directories(include)

# Buscar todas las fuentes recursivamente
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Agregar ejecutable
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        sfml-network
)

