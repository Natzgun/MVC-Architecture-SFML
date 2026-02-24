cmake_minimum_required(VERSION 3.28)
project(Revolution_Game LANGUAGES CXX)

# Configuración de salida de binarios
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Gestión de dependencias via FetchContent (SFML 3.x)
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Inclusión de directorios de cabeceras
include_directories(include)

# Búsqueda recursiva de archivos fuente
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Configuración del ejecutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Configuración de C++17
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Enlace de librerías de SFML (Formato moderno SFML::)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    SFML::Audio 
    SFML::Network
)

# Configuración para Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
