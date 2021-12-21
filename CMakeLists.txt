
cmake_minimum_required(VERSION 2.8)
set(USE_FASTLED ON)

include(tools/cmake/arduino.cmake)

project(PlayBox C CXX)

add_subdirectory(tools)

add_executable(${CMAKE_PROJECT_NAME}
    src/PlayBox.cpp
    src/Button.h
    src/Button.cpp
    src/Buzzer.h
    src/Buzzer.cpp
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

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES SUFFIX ".elf")
target_link_libraries(${CMAKE_PROJECT_NAME} arduinocore avrlib fastled)


