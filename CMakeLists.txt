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

# --- Engine module sources (DO NOT MODIFY) ---
set(ENGINE_SOURCES
    src/Engine/Core/Application.cpp
    src/Engine/Graphics/Renderer.cpp
    src/Engine/Input/InputManager.cpp
    src/Engine/Audio/AudioManager.cpp
    src/Engine/Scene/SceneManager.cpp
)

# --- Game framework sources ---
set(GAME_FRAMEWORK_SOURCES
    src/Game/Entities/Entity.cpp
    src/Game/Physics/Collision.cpp
    src/Game/Animation/SpriteAnimator.cpp
    src/Game/Camera/Camera.cpp
    src/Game/UI/HUD.cpp
)

# --- Game sources (ADD YOUR SCENES AND ENTITIES HERE) ---
set(GAME_SOURCES
    src/main.cpp
    src/Example/DemoScene.cpp
    src/Game/Scenes/MenuScene.cpp
    src/Game/Scenes/PauseScene.cpp
)

add_executable(${PROJECT_NAME} ${ENGINE_SOURCES} ${GAME_FRAMEWORK_SOURCES} ${GAME_SOURCES})

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
