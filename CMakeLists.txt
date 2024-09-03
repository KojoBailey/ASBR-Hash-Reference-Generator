cmake_minimum_required(VERSION 3.16)
project(CharIdHashPrinter C CXX)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCES "src/*.c" "src/*.cpp" "src/*.h" "src/*.hpp")

add_link_options(-static -static-libgcc -static-libstdc++)

add_library(CharIdHashPrinter SHARED ${SOURCES})

add_subdirectory(external/japi)

target_include_directories(${PROJECT_NAME} PRIVATE "src" "external/japi/src/exports")
target_include_directories(${PROJECT_NAME} PRIVATE "src" "external/binary/binary")
target_link_libraries(${PROJECT_NAME} PRIVATE d3dcompiler_47)