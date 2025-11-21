cmake_minimum_required(VERSION 3.10)

# Project Name
project(CardBattleEngine VERSION 1.0)

# Specify C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Export compile commands for Neovim LSP (clangd)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include directories (tells compiler where to find .h files)
include_directories(include)

# Define source files
# Can automate this, but listing them explicitly is safer for now
set(SOURCES
    src/main.cpp
    src/Card.cpp
    src/Player.cpp
    src/GameEngine.cpp
    src/PlayState.cpp
)

# Create the executable
add_executable(CardBattleEngine ${SOURCES})
