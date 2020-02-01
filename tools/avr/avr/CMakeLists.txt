set(FILE_SEARCH_LIST
    include/avr/*.h
    include/*.h)

file(GLOB LIB_FILES ${FILE_SEARCH_LIST})

add_library(avrlib ${LIB_FILES})

set_target_properties(avrlib PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(avrlib INTERFACE include)
