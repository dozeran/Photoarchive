
cmake_minimum_required(VERSION 3.16)

project(PhotoArchive LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

add_library(photoarchive_lib
    src/MetadataList.cpp
    src/Photo.cpp
)

target_include_directories(photoarchive_lib PUBLIC include)

target_compile_options(photoarchive_lib PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

add_executable(photoarchive
    src/main.cpp
)

target_link_libraries(photoarchive PRIVATE photoarchive_lib)

target_compile_options(photoarchive PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

if(ENABLE_SANITIZERS)
    target_compile_options(photoarchive_lib PRIVATE
        -fsanitize=address,undefined -g
    )
    target_link_options(photoarchive_lib PRIVATE
        -fsanitize=address,undefined
    )

    target_compile_options(photoarchive PRIVATE
        -fsanitize=address,undefined -g
    )
    target_link_options(photoarchive PRIVATE
        -fsanitize=address,undefined
    )
endif()

enable_testing()

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

add_executable(photoarchive_tests
    tests/test_metadata.cpp
)

target_link_libraries(photoarchive_tests PRIVATE
    photoarchive_lib
    GTest::gtest_main
)

target_compile_options(photoarchive_tests PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

include(GoogleTest)
gtest_discover_tests(photoarchive_tests)

if(ENABLE_SANITIZERS)
    target_compile_options(photoarchive_tests PRIVATE
        -fsanitize=address,undefined -g
    )
    target_link_options(photoarchive_tests PRIVATE
        -fsanitize=address,undefined
    )
endif()

add_executable(asan_double_free
    tests/asan_double_free.cpp
)

target_compile_options(asan_double_free PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

if(ENABLE_SANITIZERS)
    target_compile_options(asan_double_free PRIVATE
        -fsanitize=address,undefined -g
    )
    target_link_options(asan_double_free PRIVATE
        -fsanitize=address,undefined
    )
endif()

add_executable(vector_experiment tests/vector_experiment.cpp)

target_compile_options(vector_experiment PRIVATE
    -Wall -Wextra -Wpedantic
)

if(ENABLE_SANITIZERS)
    target_compile_options(vector_experiment PRIVATE
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
    )
    target_link_options(vector_experiment PRIVATE
        -fsanitize=address,undefined
    )
endif()