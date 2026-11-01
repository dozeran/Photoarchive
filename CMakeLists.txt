
cmake_minimum_required(VERSION 3.16)

project(PhotoArchive LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(photoarchive
    src/main.cpp
)

target_include_directories(photoarchive PRIVATE include)

target_compile_options(photoarchive PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

option(ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

if(ENABLE_SANITIZERS)
    target_compile_options(photoarchive PRIVATE
        -fsanitize=address,undefined
        -g
    )
    target_link_options(photoarchive PRIVATE
        -fsanitize=address,undefined
    )
endif()
