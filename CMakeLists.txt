cmake_minimum_required(VERSION 3.20)
project(snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

# res klasörünü build klasörüne otomatik kopyala
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(WIN32)
    target_link_libraries(snake PRIVATE user32)
endif()

# Release derlemesinde boyut optimizasyonu
if(MSVC)
    target_compile_options(snake PRIVATE
        $<$<CONFIG:Release>:/O1>
    )
else()
    target_compile_options(snake PRIVATE
        $<$<CONFIG:Release>:-Os>
    )
    target_link_options(snake PRIVATE
        $<$<CONFIG:Release>:-s>
    )
endif()