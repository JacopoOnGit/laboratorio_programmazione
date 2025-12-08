cmake_minimum_required(VERSION 4.0)
project(laboratorio_programmazione)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)
message(STATUS "SFML include dir: ${SFML_INCLUDE_DIRS}")


add_executable(laboratorio_programmazione main.cpp)

target_link_libraries(laboratorio_programmazione PRIVATE SFML::Graphics SFML::Window SFML::System)

