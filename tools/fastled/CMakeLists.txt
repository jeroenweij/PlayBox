
set(FILE_SEARCH_LIST
    *.cpp
    *.c
    *.cc
    *.cxx
    *.h
    *.hh
    *.hxx)


file(GLOB LIB_FILES ${FILE_SEARCH_LIST})

add_library(fastled ${LIB_FILES})

target_link_libraries(fastled arduinocore avrlib)

target_include_directories(fastled PUBLIC .)
