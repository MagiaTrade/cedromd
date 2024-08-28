cmake_minimum_required(VERSION 3.12)
project(cedro_md_ex VERSION 1.0 LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    cedromd
)

