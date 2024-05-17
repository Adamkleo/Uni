cmake_minimum_required(VERSION 3.0)
project(simulation_library)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add all the source files from the 'sim' directory
add_library(sim
        block.cpp
        Fluid_simulation.cpp
        Grid.cpp
        particle.cpp
        vector.cpp
)

target_include_directories(sim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
