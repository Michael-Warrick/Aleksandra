cmake_minimum_required(VERSION 3.25.3)
project(Aleksandra VERSION 0.0.1)

# Setting C++ Version to 2020
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)