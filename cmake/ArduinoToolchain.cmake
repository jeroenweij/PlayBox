#=============================================================================#
# Author: Tomasz Bogdal (QueezyTheGreat)
# Home:   https://github.com/queezythegreat/arduino-cmake
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at http://mozilla.org/MPL/2.0/.
#=============================================================================#
set(CMAKE_SYSTEM_NAME Arduino)

set(CMAKE_C_COMPILER   avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

set(TOOLS_PATH "${CMAKE_SOURCE_DIR}/tools/")

# Add current directory to CMake Module path automatically
if(EXISTS  ${CMAKE_CURRENT_LIST_DIR}/Platform/Arduino.cmake)
    set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR})
endif()

#=============================================================================#
#                         System Paths                                        #
#=============================================================================#
include(Platform/UnixPaths)

list(APPEND CMAKE_SYSTEM_PREFIX_PATH ${TOOLS_PATH}avr)
list(APPEND CMAKE_SYSTEM_PREFIX_PATH ${TOOLS_PATH}avr/utils)


