cmake_minimum_required(VERSION 3.17)
project(search_engine VERSION 1.0)
set(CMAKE_CXX_STANDART 14)

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(MY_SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_subdirectory(nlohmann_json)

add_subdirectory(src)
add_subdirectory(tests)