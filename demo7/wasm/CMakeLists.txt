cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Demo7 VERSION 1.0)

set(CMAKE_VERBOSE_MAKEFILE on)

# add the executable
add_executable(demo7 demo7.c)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(CMAKE_C_COMPILER "emcc")
    set(EXPORTED_FUNCTIONS "[_add,_abs]")
    set_target_properties(demo7 PROPERTIES LINK_FLAGS "\
        -s NO_FILESYSTEM \
        -s INITIAL_MEMORY=1MB \
        -s STACK_SIZE=128KB \
        -s ENVIRONMENT='web' \
        -s FILESYSTEM=0 \
        -s EXPORT_ES6=1 \
        --no-entry \
        -s EXPORTED_FUNCTIONS='${EXPORTED_FUNCTIONS}' \
      ")
endif ()
