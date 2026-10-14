cmake_minimum_required(VERSION 3.20)
project(snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(snake
    src/main.cpp
    src/classes.cpp
    src/draw.cpp
    src/food.cpp
    src/input.cpp
    src/terminal.cpp
    src/checks.cpp
    src/screen.cpp
)

target_include_directories(snake PRIVATE include)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/res"
     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(snake PRIVATE
        $<$<CONFIG:Release>:-Os>
        $<$<CONFIG:Release>:-ffunction-sections>
        $<$<CONFIG:Release>:-fdata-sections>
    )

    target_link_options(snake PRIVATE
        $<$<CONFIG:Release>:-s>
        $<$<CONFIG:Release>:-Wl,--gc-sections>
    )
endif()