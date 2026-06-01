cmake_minimum_required(VERSION 4.3)
project(SFML_Chess_Portfolio CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML dependencies
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Include directories
include_directories(include)

# Gather source files
file(GLOB SOURCES "src/*.cpp")

# Define execution target
add_executable(ChessGame ${SOURCES})
target_link_libraries(ChessGame sfml-graphics sfml-window sfml-system)