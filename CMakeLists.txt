

set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake)

cmake_minimum_required(VERSION 2.8)

project(ThijsBox C CXX)

set(ThijsBox_SOURCES
    src/main.cpp
    src/Button.h
    src/Button.cpp
    src/Program.h
    src/Program.cpp
    src/InitProgram.h
    src/InitProgram.cpp
    src/ToggleProgram.h
    src/ToggleProgram.cpp
    src/ColorWheelProgram.h
    src/ColorWheelProgram.cpp
    src/SimonProgram.h
    src/SimonProgram.cpp
    src/WhackAMoleProgram.h
    src/WhackAMoleProgram.cpp
    src/MixUpProgram.h
    src/MixUpProgram.cpp
    src/LowPowerProgram.h
    src/LowPowerProgram.cpp
    src/TicTacToeProgram.h
    src/TicTacToeProgram.cpp
    src/ColorPickerProgram.h
    src/ColorPickerProgram.cpp
    src/Leds.h
    src/Leds.cpp
    )

add_subdirectory(tools)

add_executable(${CMAKE_PROJECT_NAME} ${ThijsBox_SOURCES})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES SUFFIX ".elf")
target_link_libraries(${CMAKE_PROJECT_NAME} arduinocore avrlib fastled)


