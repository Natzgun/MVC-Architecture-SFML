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

# --- Example sources (reference code — add your own scenes and entities here) ---
set(EXAMPLE_SOURCES
    src/main.cpp
    src/Example/DemoScene.cpp
    src/Example/Entities/Entity.cpp
    src/Example/Physics/Collision.cpp
    src/Example/Animation/SpriteAnimator.cpp
    src/Example/Camera/Camera.cpp
    src/Example/UI/HUD.cpp
    src/Example/Scenes/MenuScene.cpp
    src/Example/Scenes/PauseScene.cpp
)

add_executable(${PROJECT_NAME} ${ENGINE_SOURCES} ${EXAMPLE_SOURCES})

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
