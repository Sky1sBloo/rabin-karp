cmake_minimum_required(VERSION 3.30)

project(rabin-karp LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
add_executable(rabin-karp main.cpp)
target_link_libraries(rabin-karp PRIVATE rabin-karp-lib)
add_subdirectory(tests)
