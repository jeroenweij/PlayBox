
set(FILE_SEARCH_LIST
    *.cpp
    *.c
    *.cc
    *.cxx
    *.h
    *.hh
    *.hxx)


file(GLOB LIB_FILES ${FILE_SEARCH_LIST})

add_library(arduinocore ${LIB_FILES})

target_link_libraries(arduinocore avrlib)

target_include_directories(arduinocore PUBLIC .)
