cmake_minimum_required(VERSION 3.28)
project(SFMLGameTemplate LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- SFML 3.0 via FetchContent ---
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# --- Engine core sources ---
set(ENGINE_SOURCES
    src/Core/Game.cpp
    src/States/StateMachine.cpp
)

# --- Example sources (replace these with your own game files) ---
set(GAME_SOURCES
    src/main.cpp
    src/Example/DemoState.cpp
)

add_executable(${PROJECT_NAME} ${ENGINE_SOURCES} ${GAME_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Link only the SFML modules you need.
# Remove SFML::Audio or SFML::Network if your game doesn't use them.
target_link_libraries(${PROJECT_NAME} PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
    SFML::Network
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
