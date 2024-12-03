#cmake_minimum_required(VERSION 3.17)

set(JSON_BuildTests OFF CACHE INTERNAL "")

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
add_executable(search_engine main.cpp ${MY_INCLUDE_DIR}/converterJSON.h converterJSON.cpp ${MY_INCLUDE_DIR}/invertedIndex.h invertedIndex.cpp ${MY_INCLUDE_DIR}/searchServer.h searchServer.cpp) # my-math.cpp ${MY_INCLUDE_DIR}/struct.h
target_include_directories(search_engine PUBLIC ${MY_INCLUDE_DIR})
#${MY_INCLUDE_DIR}/my-math.h

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

