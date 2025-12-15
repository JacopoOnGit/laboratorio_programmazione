cmake_minimum_required(VERSION 4.0)
project(laboratorio_programmazione)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_library(core
        src/resource_loader.cpp
)

target_include_directories(core PUBLIC src)

add_executable(laboratorio_programmazione
        main.cpp
)

target_link_libraries(laboratorio_programmazione
        PRIVATE
        core
        SFML::Graphics
        SFML::Window
        SFML::System
)

# Test

enable_testing()
find_package(GTest REQUIRED)

add_executable(resource_loader_tests
        tests/resource_loader_test.cpp
        tests/resource_loader_test.cpp
)

target_link_libraries(resource_loader_tests
        PRIVATE
        core
        GTest::gtest
        GTest::gtest_main
)

add_test(NAME ResourceLoaderTests COMMAND resource_loader_tests)
