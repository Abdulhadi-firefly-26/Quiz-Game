cmake_minimum_required(VERSION 3.10)   # Sets required minimum CMake version
project(MyCppProject VERSION 1.0)      # Names your project

set(CMAKE_CXX_STANDARD 17)             # Configures C++ standard 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiles main.cpp into an executable named MyCppProject
add_executable(MyCppProject src/main.cpp) 