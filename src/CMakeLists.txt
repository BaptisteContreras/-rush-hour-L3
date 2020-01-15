cmake_minimum_required(VERSION 3.6)
# Replace VisionTest with your project name
project(rush)
set(MY_SOURCE_DIR /home/jbdargier/CLionProjects/rush-hour-etu/src)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp )
include_directories(${MY_SOURCE_DIR}/class)
file(GLOB SOURCES class/header/*.h class/builder/*.cpp class/Affichage/*.cpp class/*.cpp class/structs/*.cpp class/tests/*.cpp class/enum/*.h)

# This is to compile main.cpp into an executable named vision_test
add_executable(rush main.cpp ${SOURCE_FILES} ${SOURCES})
