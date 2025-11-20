cmake_minimum_required(VERSION 3.15)

add_library(algorithm_lib STATIC
    src/util.cpp
    src/sort.cpp
    src/tree.cpp
)

target_include_directories(algorithm_lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(algorithm_lib PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-fPIC>
)

set_target_properties(algorithm_lib PROPERTIES
    OUTPUT_NAME "algorithm"
    VERSION 1.0.0
    SOVERSION 1
    POSITION_INDEPENDENT_CODE ON
)

install(TARGETS algorithm_lib
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
)
