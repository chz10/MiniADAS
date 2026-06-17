cmake_minimum_required(VERSION 3.20)

project(MiniADAS_CPP
    VERSION 0.2.0
    DESCRIPTION "C++ ADAS perception evaluation and visualization tool"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(mini_adas_eval
    src/main.cpp
)

target_include_directories(mini_adas_eval
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(mini_adas_eval
    PRIVATE
        $<$<CXX_COMPILER_ID:Clang,AppleClang,GNU>:-Wall -Wextra -Wpedantic>
)
