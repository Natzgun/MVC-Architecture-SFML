cmake_minimum_required(VERSION 3.25)
project(MVC_Architecture_SFML)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(MVC_Architecture_SFML main.cpp Model/Model.cpp Model/Model.h View/View.cpp View/View.h Controller/Controller.cpp Controller/Controller.h)
target_link_libraries(MVC_Architecture_SFML sfml-system sfml-window sfml-graphics sfml-audio sfml-network)