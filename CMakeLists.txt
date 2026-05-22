cmake_minimum_required(VERSION 3.10)

project(skinhook)

set(CMAKE_CXX_STANDARD 17)

add_library(skinhook SHARED src/main_minimal.cpp)
target_link_libraries(skinhook log dl)

set(CMAKE_C_FLAGS_RELEASE "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -DNDEBUG")
