cmake_minimum_required(VERSION 3.12)
project(cedromd VERSION 1.0 LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 17)

option(CMD_BUILD_TESTS "Build the tests" ON)
option(CMD_BUILD_EXAMPLES "Build the examples" ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/cedro_md.cmake)

if(EXISTS "${CMAKE_SOURCE_DIR}/cmake/env.local.cmake")
    include(${CMAKE_SOURCE_DIR}/cmake/env.local.cmake)
else()
    message(FATAL_ERROR "The env.local.cmake file was not found. Please create it from the env.template.cmake. See readme.md for Authentication instructions!")
endif()

add_library(${PROJECT_NAME}
    ${CMD_HEADERS}
    ${CMD_SRCS}
)

add_executable(test-credentials
    main.cpp
)

add_compile_definitions(
    CEDRO_USERNAME="${CEDRO_USERNAME}"
    CEDRO_PASSWORD="${CEDRO_PASSWORD}"
    CEDRO_SOFTKEY="${CEDRO_SOFTKEY}"
)

add_subdirectory(beastboys)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMD_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    beast_boys
)

set(BUILD_BB_TESTS ON)

if (${CMD_BUILD_TESTS})
    add_subdirectory(tests)
endif()

if (${CMD_BUILD_EXAMPLES})
    add_subdirectory(examples)
endif()

