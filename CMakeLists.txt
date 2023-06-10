cmake_minimum_required(VERSION 3.25)
project(MVC_Architecture_SFML)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(MVC_Architecture_SFML main.cpp Model/Modelo.cpp Model/Modelo.h View/Vista.cpp View/Vista.h Controller/Controlador.cpp Controller/Controlador.h)
target_link_libraries(MVC_Architecture_SFML sfml-system sfml-window sfml-graphics sfml-audio sfml-network)