cmake_minimum_required(VERSION 3.20)

project(rustiq_ai
    VERSION 1.0
    DESCRIPTION "rustiq_ai"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE CORE_SRC
    ${CMAKE_SOURCE_DIR}/ai/src/*.cpp
)

add_executable(${PROJECT_NAME} ${CORE_SRC})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/ai/include
        ${CMAKE_SOURCE_DIR}/ai/src
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall -Wextra -Werror
)
