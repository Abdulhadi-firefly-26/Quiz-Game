cmake_minimum_required(VERSION 3.10) 
project(MyCppProject VERSION 1.0)  

set(CMAKE_CXX_STANDARD 17)             
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MyCppProject src/main.cpp)
target_compile_definitions(MyCppProject PRIVATE
    QUIZ_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/txt_files"
)