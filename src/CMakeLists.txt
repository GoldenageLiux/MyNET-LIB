file(GLOB_RECURSE lib_sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(lib_shared SHARED ${lib_sources})